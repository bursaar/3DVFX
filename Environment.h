#ifndef _ENVIRONMENT_H_
#define _ENVIRONMENT_H_

#ifndef _RENDEREVENT_H_
#include "RenderEvent.h"
#endif //_RENDEREVENT_H_

class Model;

class Environment : public RenderEvent
{
public:
	Environment(void);
	~Environment(void);

	void LoadEnvironment(const char* ID,const char* fileName, Vector3D pos, Vector3D rot, float scale);

	virtual void Render();

	void SetUVMulitply(int UVM);



private:

	Model* m_model;
	MyString m_ID;

	int m_UVMultiply;
};


#endif //_ENVIRONMENT_H_