/****************************************************************************/
////////////////////////////////// include ///////////////////////////////////
/****************************************************************************/
#include <DL_PreCompile.h>
#include "DL_PrimitiveBoxNode.h"

namespace DL
{

//============================================================================
//! ���`��
void C_PrimitiveBoxNode::_Render(void)
{
#ifdef WIN32
	//���_�ݒ�
	const S_Vector2 pos_S = GetPosition();
	const S_Color color_S = GetColor();

	//���_�ݒ�
	S_RHW_Vertex vertex_SA[4] = {
		{ 0, 0, 0, 1, S_Color::PackARGB(color_S) },
		{ 0, 0, 0, 1, S_Color::PackARGB(color_S) },
		{ 0, 0, 0, 1, S_Color::PackARGB(color_S) },
		{ 0, 0, 0, 1, S_Color::PackARGB(color_S) }
	};

	const S_Vector2 origin_S = GetOrigin();
	const S_Vector2 rotate_Origin_S = GetRotateOrigin();

	const DL::S_Vector2 left_Bottom(pos_S.x - _box_S.size_S.x * origin_S.x , pos_S.y - _box_S.size_S.y * origin_S.y);
	const DL::S_Vector2 right_Up(left_Bottom.x + _box_S.size_S.x , left_Bottom.y + _box_S.size_S.y);

	//��]����
	if(static_cast<dlS32>(_degree) % 360 != 0)
	{
		//��]�̊�_�����_�ɂȂ�悤�ɐݒ�
		vertex_SA[0].x = vertex_SA[3].x = -_box_S.size_S.x * rotate_Origin_S.x;
		vertex_SA[0].y = vertex_SA[1].y = -_box_S.size_S.y * rotate_Origin_S.y;
		vertex_SA[1].x = vertex_SA[2].x = vertex_SA[0].x + _box_S.size_S.x;
		vertex_SA[2].y = vertex_SA[3].y = vertex_SA[0].y + _box_S.size_S.y;

		dlF32 sin_Value = DL::MATH::Sin(DL::MATH::DegToRad(_degree));
		dlF32 cos_Value = DL::MATH::Cos(DL::MATH::DegToRad(_degree));
		S_Vector2 turn_SA[4];
		for(dlS32 i = 0 ; i < 4 ; ++ i)
		{
			turn_SA[i] = S_Vector2(
				vertex_SA[i].x * cos_Value - vertex_SA[i].y * sin_Value,
				vertex_SA[i].x * sin_Value + vertex_SA[i].y * cos_Value
			);
		}

		//���Z
		/*�t���b�v��*/
		//if(IsFlipFlg())
		{
			/*
			vertex_SA[0].x = -turn_SA[3].x + pos_S.x;
			vertex_SA[0].y = turn_SA[3].y + pos_S.y;

			vertex_SA[1].x = -turn_SA[2].x + pos_S.x;
			vertex_SA[1].y = turn_SA[2].y + pos_S.y;

			vertex_SA[2].x = -turn_SA[1].x + pos_S.x;
			vertex_SA[2].y = turn_SA[1].y + pos_S.y;

			vertex_SA[3].x = -turn_SA[0].x + pos_S.x;
			vertex_SA[3].y = turn_SA[0].y + pos_S.y;*/
		}
		/*�ʏ�*/
		//else
		{
			for(dlS32 i = 0 ; i < 4 ; ++ i)
			{
				vertex_SA[i].x = turn_SA[i].x + pos_S.x;
				vertex_SA[i].y = turn_SA[i].y + pos_S.y;
			}
		}
	}
	else
	{
		//�\����_�𔽉f������悤�Ɉړ�
		vertex_SA[0].x = vertex_SA[3].x = left_Bottom.x;
		vertex_SA[0].y = vertex_SA[1].y = left_Bottom.y;
		vertex_SA[1].x = vertex_SA[2].x = right_Up.x;
		vertex_SA[2].y = vertex_SA[3].y = right_Up.y;
	}

	//���_�X�g���[���錾�ݒ�
	_GetDevice() -> GetDevice() -> SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

	//�|���S���̕`��
	_GetDevice() -> GetDevice() -> DrawPrimitiveUP(D3DPT_TRIANGLEFAN , 2 , vertex_SA , sizeof(S_RHW_Vertex));
#endif
}

}