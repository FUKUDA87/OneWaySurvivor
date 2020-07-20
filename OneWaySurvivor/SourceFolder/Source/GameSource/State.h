#pragma once
#include<d3dx9.h>
#include"Struct.h"

//動き用
class StateMove {
public:
	virtual StateMove* Action(ObjectParts *ObjPar) = 0;//=0:純粋仮想関数にする（必ず継承し、派生クラス側でオーバーライドしないといけない関数
};


class StateDraw3D {
public:
	virtual StateDraw3D* Action(Object3D *Object) = 0;//=0:純粋仮想関数にする（必ず継承し、派生クラス側でオーバーライドしないといけない関数
};