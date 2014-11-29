

///矢印描画情報
struct S_DrawRay
{

	///基準点の移動率
	///@note 0.0 : 基準点は矢印の最後尾
	///      1.0 : 基準点は矢印の先端
	dlF32     origin;
	///回転角（0°～360°）
	dlF32     degree;

	///先端部の辺の半分の長さ
	dlF32     radius;
	///先端部までの幅の半分
	dlF32     half_Length;
	///先端部までの長さ
	dlF32     width;
};
