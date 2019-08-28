#include "Canon_Camera.h"


	bool Canon_Camera::Speed_auto_Lessen()
	{
		m_fSpeed -= David_SecPerFrame;
		if (m_fSpeed < 0.5f) m_fSpeed = 0.5f;

		return true;
	}

	void Canon_Camera::Set_View_Matrix(
		D3DXVECTOR3 camera_position_in ,
		D3DXVECTOR3 fake_up_in,
		D3DXVECTOR3 Target_at_in)

	{
		camera_position = camera_position_in;
		fake_up = fake_up_in;
		Target_at = Target_at_in;

		D3DXMatrixLookAtLH(&m_matView,
			&camera_position,
			&Target_at,
			&fake_up); // �� ��� ��ȯ

		camera_Coordinates_System_from_ViewMatrix_and_YawPitch_Roll_from_LookVector(); // ViewMatrix�� ������, �װɷ� CoordinateSystem�� ����ġ�� ������Ʈ�Ѵ�.

	}

	bool Canon_Camera::ViewMatrix_Update_From_Keyboard_Mouse(D3DXVECTOR4 vValue) // �̰� �ٽ��̴�. ����4 vValue�� �Ѿ���� �� ����.
	{
		// yaw, pitch,roll, radius
		D3DXMATRIX matRotation;
		D3DXQUATERNION qRotation;

		D3DXQuaternionRotationYawPitchRoll(&qRotation, // �װ� ������, ���ʹϿ��� �����.
			m_fCameraYawAngle += vValue.y,
			m_fCameraPitchAngle += vValue.x,
			m_fCameraRollAngle += vValue.z); // ���콺 z��ǥ �� �� ����.

		D3DXMatrixAffineTransformation(&matRotation, 1.0f, NULL, &qRotation, &camera_position); // ������, ȸ��, �̵���� ������ �ϳ��� ��������� �����.
		D3DXMatrixInverse(&m_matView, NULL, &matRotation); // �и��� ī�޶�� ��ü���� �� �ݴ�� �����δ�. ������̴�.

		camera_Coordinates_System_from_ViewMatrix_and_YawPitch_Roll_from_LookVector();

		return true;
	}


	void Canon_Camera::Set_Projection_Matrix(float Vertical_Fov_Angle_in, float Aspect_Ratio_in, float Near_Plane_Distance_in, float Far_Plane_Distance_in)
	{
		Vertical_Fov_Angle = Vertical_Fov_Angle_in;
		Aspect_Ratio = Aspect_Ratio_in;
		Near_Plane_Distance = Near_Plane_Distance_in;
		Far_Plane_Distance = Far_Plane_Distance_in;

		D3DXMatrixPerspectiveFovLH(&m_matProj,
			(float)D3DX_PI * Vertical_Fov_Angle,
			Aspect_Ratio,
			Near_Plane_Distance,
			Far_Plane_Distance);
	}

	void Canon_Camera::Move_on_Look_line(float fValue)
	{
		camera_position += camera_look * fValue*m_fSpeed; // ī�޶� Look������ �̵�.
	}

	void Canon_Camera::Move_on_Right_line(float fValue)
	{
		camera_position += camera__Right * fValue*m_fSpeed; // ī�޶� Right ���������� �̵�.
	}

	void Canon_Camera::Move_on_Up_line(float fValue)
	{
		camera_position += camera_up * fValue*m_fSpeed; // ī�޶� UP ���������� �̵�.
	}

	void Canon_Camera::SetSpeed(float fValue)
	{
		m_fSpeed += fValue;
	}



	bool Canon_Camera::camera_Coordinates_System_from_ViewMatrix_and_YawPitch_Roll_from_LookVector() // ViewMatix�� ������Ʈ �Ǿ �Ѿ����, ī�޶� Coordinate System �� ����ġ���� �ǽð� ������Ʈ �մϴ�.
	{
		camera__Right.x = m_matView._11; camera_up.x = m_matView._12;   camera_look.x = m_matView._13;
		camera__Right.y = m_matView._21; camera_up.y = m_matView._22;   camera_look.y = m_matView._23;
		camera__Right.z = m_matView._31; camera_up.z = m_matView._32;   camera_look.z = m_matView._33;

		D3DXMATRIX m_Inverse_ViewMatrix;
		D3DXMatrixInverse(&m_Inverse_ViewMatrix, NULL, &m_matView);
		D3DXVECTOR3* camera_look_vectors_ptr = (D3DXVECTOR3*)&m_Inverse_ViewMatrix._31;

		m_fCameraYawAngle = atan2f(camera_look_vectors_ptr->x, camera_look_vectors_ptr->z);
		float fLen = sqrtf(camera_look_vectors_ptr->z * camera_look_vectors_ptr->z + camera_look_vectors_ptr->x * camera_look_vectors_ptr->x);
		m_fCameraPitchAngle = -atan2f(camera_look_vectors_ptr->y, fLen);

		return true;
	}


	Canon_Camera::Canon_Camera()
	{
		m_fCameraYawAngle = 0.0f;
		m_fCameraPitchAngle = 0.0f;
		m_fCameraRollAngle = 0.0f;
		m_fSpeed = 1.0f;
	}

	void Canon_Camera::camera_operation()
	{
		D3DXVECTOR4   vYawPitchRoll(0, 0, 0, 0);
	


		// ��
		if(g_Input.Yaw_clock)
		{
			vYawPitchRoll.x += 0.1f*David_SecPerFrame;
		}

		if (g_Input.Yaw_a_clock)
		{
			vYawPitchRoll.x -= 0.1f*David_SecPerFrame;
		}

		// ��ġ

		if (g_Input.Pitch_clock)
		{
			vYawPitchRoll.y += 0.1f*David_SecPerFrame;
		}

		if (g_Input.Pitch_a_clock)
		{
			vYawPitchRoll.y -= 0.1f*David_SecPerFrame;
		}

		// ��

		if (g_Input.Roll_clock)
		{
			vYawPitchRoll.z += 0.1f*David_SecPerFrame;
		}

		if (g_Input.Roll_a_clock)
		{
			vYawPitchRoll.z -= 0.1f*David_SecPerFrame;
		}


		// ���ǵ� �ν���
		if (g_Input.bJump)
		{
			this->SetSpeed(David_SecPerFrame*3.0f);
		}

		//// �� �Ʒ� ����


		//if (g_Input.Yaw_clock)
		//{
		//	this->Move_on_Up_line(-g_fSecPerFrame * 5.0f);

		//}

		//if (g_Input.Yaw_clock)
		//{
		//	this->Move_on_Up_line(g_fSecPerFrame*5.0f);
		//}

		// ��,�� ����

	

		if (g_Input.bFront)
		{
			this->Move_on_Look_line(-David_SecPerFrame * 5.0f);

		}

		if (g_Input.bBack)
		{
			this->Move_on_Look_line(David_SecPerFrame * 5.0f);

		}

		// �� �� �� ����

		if (g_Input.bLeft)
		{
			this->Move_on_Right_line(-David_SecPerFrame * 5.0f);
		}

		if (g_Input.bRight)
		{
			this->Move_on_Right_line(David_SecPerFrame*5.0f);
		}

		this->ViewMatrix_Update_From_Keyboard_Mouse(vYawPitchRoll);

	}