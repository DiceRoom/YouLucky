/****************************************************************************/
/* DL_2DFrameWorkDrawPrimitive.h											*/
/****************************************************************************/
#ifndef DL_2DFRAMEWORKDRAWPRIMITIVE_H_
#define	DL_2DFRAMEWORKDRAWPRIMITIVE_H_

/****************************************************************************/
////////////////////////////// Type Declaration //////////////////////////////
/****************************************************************************/

namespace DL
{

class C_DirectXDevice;

//! 2Dゲーム用フレームワーク(プリミティブの描画)
class C_DL2DFrameWorkDrawPrimitive
{
friend class C_DL2DFrameWork;
private:
	//コンストラクタ、コピーコンストラクタ、デストラクタの禁止
	C_DL2DFrameWorkDrawPrimitive(void){}
	~C_DL2DFrameWorkDrawPrimitive(void){}
	C_DL2DFrameWorkDrawPrimitive(const C_DL2DFrameWorkDrawPrimitive &){}

public:
	void Initialize				(void);
	void Terminate				(void){};

	template<class PRIMITIVE_CLASS_NAME>
	static PRIMITIVE_CLASS_NAME* GetPrimitive(const S_Vector2& pos_S , const S_Color& color_S , dlS32 depth , dlBOOL virtual_Flip_Flg);

	NODE_HANDLE CreateCircle	(const S_Vector2&	pos_S,
								 dlF32				radius,
								 const S_Color&		color_S,
								 dlS32				depth,
								 dlBOOL				virtual_Flip_Flg);

	NODE_HANDLE CreateLine		(const S_Vector2&	pos_S,
								 const S_Vector2&	line_S,
								 const S_Color&		color_S,
								 dlS32				depth,
								 dlBOOL				virtual_Flip_Flg);
	
	NODE_HANDLE CreateBox		(const S_Vector2&	pos_S,
								 const S_Vector2&	size_S,
								 const S_Color&		color_S,
								 const S_Vector2&	origin_S,
								 const S_Vector2&	rotate_Origin_S,
								 dlF32				degree,
								 dlS32				depth,
								 dlBOOL				virtual_Flip_Flg);

	NODE_HANDLE CreatePolygon	(const S_Vector2&				pos_S,
								 const std::vector<S_Vector2>&	vertex_List,
								 const S_Color&					color_S,
								 dlS32							depth,
								 dlBOOL							virtual_Flip_Flg);
	
	
	NODE_HANDLE CreateRay		(const S_Vector2&				pos_S,
								 dlF32							origin,
								 dlF32							degree,
								 dlF32							radius,
								 dlF32							half_Length,
								 dlF32							width,
								 const S_Color&					color_S,
								 dlS32							depth,
								 dlBOOL							virtual_Flip_Flg);

	dlBOOL	DeletePrimitive	(DL::NODE_HANDLE handle);

	dlBOOL	SetPosition		(NODE_HANDLE handle , const S_Vector2& pos_S);
	dlBOOL	SetRotate		(NODE_HANDLE handle , dlF32 degree);
	dlBOOL	SetDepth		(NODE_HANDLE handle , dlS32 depth);
	dlBOOL	SetValidFlg		(NODE_HANDLE handle , dlBOOL flg);
	dlBOOL	SetColor		(NODE_HANDLE handle , const S_Color& color_S);
	dlBOOL	SetOrigin		(NODE_HANDLE handle , const S_Vector2& origin_S , const S_Vector2& rotate_Origin_S);

	dlBOOL	IsValidFlg		(NODE_HANDLE handle , dlBOOL& out_Flg) const;

private:
	//! 登録されているプリミティブの数
	ACS_G_MEB(private , dlU32		, _primitive_Val		, PrimitiveVal);
};

}

#endif