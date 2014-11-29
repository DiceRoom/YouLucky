/****************************************************************************/
/* DL_2DFrameWorkUtility.h													*/
/****************************************************************************/
#ifndef DL_2DFRAMEWORKUTILITY_H_
#define	DL_2DFRAMEWORKUTILITY_H_

/****************************************************************************/
////////////////////////////// Type Declaration //////////////////////////////
/****************************************************************************/

namespace DL
{

//! 2Dゲーム用フレームワーク(便利機能)
class C_DL2DFrameWorkUtility
{
friend class C_DL2DFrameWork;
private:
	//コンストラクタ、コピーコンストラクタ、デストラクタの禁止
	C_DL2DFrameWorkUtility	(void){}
	~C_DL2DFrameWorkUtility	(void){}
	C_DL2DFrameWorkUtility	(const C_DL2DFrameWorkUtility &){}

public:
	void Initialize(void);
	void Terminate(void);
	
	dlS32		GetRandom			(dlS32 random_Area)					const;
	dlPCSTR		GetDIKKeyName		(dlU8 key_No)						const;
	dlSTRING	TransNumberToString	(dlS32 number , dlS32 figure = 0)	const;

private:
	std::list<dlS32> _unique_Number_List;
};

}

#endif
