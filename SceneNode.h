#ifndef _SCENENODE_H_
#define _SCENENODE_H_
#include <stdio.h>
#include <list>
#include <ddraw.h>
#include "Vector2D.h"
#include "MyString.h"
//////////////////////////////////////////////////////////////
//This is the SceneNode class.
//
//It is designed as a base class and therefore can be applied to a number
//of different classes (we can tell that this is a base class due to the virtual method calls)
//
//then applied to a class, it will allow that class to become both a parent and a child of 
//any class. it will also allow you to call a update on a node, then what update will also
//effect each of thats nodes children, and subsenquently children's children etc.
//Render calls can also be controlled if they are required. 
//
//Each Child also has a link back to it parent, in case the child's actions can effect the parent
//////////////////////////////////////////////////////////////

class SceneNode
{
public:
	//////////////////////////////////////////////
	//Default Constructor
	//////////////////////////////////////////////
	SceneNode(void){m_parent = 0;};
	//////////////////////////////////////////////
	//Destructor which can be overriden
	//////////////////////////////////////////////
	virtual ~SceneNode(void) {Destory();};
	//////////////////////////////////////////////
	//Get Type
	//
	//This will return a type defined by the user
	//it can be used to define what class the SceneNode is apart of.
	//////////////////////////////////////////////
	virtual const char* GetType() {return "SceneNode";};
	
	//////////////////////////////////////////////
	//Update Method which loops through each of the nodes childrem
	//then runs there update method, can be overriddden
	//////////////////////////////////////////////
	virtual void Update(float elapsedTime)
	{
		for(std::list<SceneNode*>::iterator i = m_children.begin(); i != m_children.end(); i++)
		{
			(*i)->Update(elapsedTime);
		}
	};

	//////////////////////////////////////////////
	//Render Method
	//////////////////////////////////////////////
	virtual void Render(LPDIRECTDRAWSURFACE7 &Surface) {};
	virtual void Render(LPDIRECTDRAWSURFACE7 &Surface, Vector2D &offset) {};

	//////////////////////////////////////////////
	//AddChild, adds a child node to this node
	//////////////////////////////////////////////
	void AddChild(SceneNode* Node)
	{
		Node->SetParent(this);
		m_children.push_back(Node);
	};

	//////////////////////////////////////////////
	//Release, deleted the pointer to this.
	//////////////////////////////////////////////
	void Release() {delete this;};

	//////////////////////////////////////////////
	//Destory, deleted all children
	//////////////////////////////////////////////
	void Destory()
	{
		for(std::list<SceneNode*>::iterator i = m_children.begin(); i != m_children.end(); i++)
		{
			(*i)->Release();
		}
		m_children.clear();
	};

	//////////////////////////////////////////////
	//removeChild, Removes Children of a certain ID
	//////////////////////////////////////////////
	void RemoveChild(const char* ID)
	{
		for(std::list<SceneNode*>::iterator i = m_children.begin(); i != m_children.end(); i++)
		{
			if(strcmp((*i)->GetID(),ID) == 0)
			{
				m_children.erase(i);
			}
			(*i)->Release();
		}
		//m_children.clear();
	};
	//////////////////////////////////////////////
	//GetChild, return a child that matches the ID
	//////////////////////////////////////////////
	virtual SceneNode* GetChild(const char* ID)
	{
		for(std::list<SceneNode*>::iterator i = m_children.begin(); i != m_children.end(); i++)
		{
			if(strcmp(ID,(*i)->GetID()) == 0)
			{
				return (*i);
			}
		}

		return 0;
	};
	//////////////////////////////////////////////
	//GetParent, Gets the parent of this node if it has one
	//////////////////////////////////////////////
	SceneNode* GetParent()
	{
		return m_parent;
	};
	//////////////////////////////////////////////
	//SetParent, Gets the parent of this node
	//////////////////////////////////////////////
	void SetParent(SceneNode* parent)
	{
		m_parent = parent;
	};
	//////////////////////////////////////////////
	//SetID, Sets the id of the node
	//////////////////////////////////////////////
	void SetID(const char* ID) 
	{
		m_ID = ID;
	};
	//////////////////////////////////////////////
	//GetID, Gets the id of the node
	//////////////////////////////////////////////
	const char* GetID() 
	{
		return m_ID;
	};

	virtual void OnLostDevice(){};

protected:
	//children list
	std::list<SceneNode*> m_children;
	//parent node
	SceneNode* m_parent;
	//ID
	MyString m_ID;
};

#endif //_SCENENODE_H_
