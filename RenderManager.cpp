#include "Types.h"
#include "RenderEvent.h"
#include "RenderManager.h"
#include "EffectManager.h"
#include "Effect.h"
#include "CameraController.h"

DefineSingleton(RenderManager);

RenderManager::RenderManager(void) :
	m_firstEvent(NULL)
{
}

RenderManager::~RenderManager(void)
{
}

void
RenderManager::AddEvent(RenderEvent* e, RenderEvent* parent)
{
	if (parent)
	{
		if (parent->m_firstChild)
		{
			RenderEvent* sibling = parent->m_firstChild;
			while (sibling->m_nextSibling)
			{
				sibling = sibling->m_nextSibling;
			}

			sibling->m_nextSibling = e;
		}
		else
		{
			parent->m_firstChild = e;
		}
	}
	else
	{
		if (m_firstEvent)
		{
			RenderEvent* sibling = m_firstEvent;
			while (sibling->m_nextSibling)
			{
				sibling = sibling->m_nextSibling;
			}

			sibling->m_nextSibling = e;
		}
		else
		{
			m_firstEvent = e;
		}

	}
}

void
RenderManager::RemoveEvent(RenderEvent* e)
{
	if (m_firstEvent)
	{
		if (m_firstEvent == e)
		{
			m_firstEvent = NULL;
		}
		else
		{
			RemoveEvent(e, m_firstEvent);
		}
	}
}

void
RenderManager::RemoveEvent(RenderEvent* e, RenderEvent* searchPosition)
{
	if (searchPosition->m_firstChild)
	{
		if (searchPosition->m_firstChild == e)
		{
			searchPosition->m_firstChild = e->m_nextSibling;
		}
		else
		{
			RemoveEvent(e, searchPosition->m_firstChild);
		}
	}

	if (searchPosition->m_nextSibling)
	{
		if (searchPosition->m_nextSibling == e)
		{
			searchPosition->m_nextSibling = e->m_nextSibling;
		}
		else
		{
			RemoveEvent(e, searchPosition->m_nextSibling);
		}
	}
}

void
RenderManager::Render()
{
	if (m_firstEvent)
	{
		
		UINT numPasses = 0;

		EffectManager::GetInstance()->GetEffect("VertexBlend")->SetVector3("m_LightDirection",Vector3D(-1, 0.75f,0.1f));
		EffectManager::GetInstance()->GetEffect("VertexBlend")->SetVector3("m_EyePosition",Vector3D(CameraController::GetInstance()->GetCurrentCameraPosition()));
		EffectManager::GetInstance()->GetEffect("VertexBlend")->SetMatrix("m_View",CameraController::GetInstance()->GetView());
		EffectManager::GetInstance()->GetEffect("VertexBlend")->SetMatrix("m_Projection",CameraController::GetInstance()->GetProjection());

		EffectManager::GetInstance()->GetEffect("VertexBlend")->SetActive(true);
		EffectManager::GetInstance()->GetEffect("VertexBlend")->GetEffect()->Begin(&numPasses,0);
		EffectManager::GetInstance()->GetEffect("VertexBlend")->GetEffect()->BeginPass(0);

		RecursiveRender(m_firstEvent, RenderEvent::Skinned);

		EffectManager::GetInstance()->GetEffect("VertexBlend")->GetEffect()->EndPass();
		EffectManager::GetInstance()->GetEffect("VertexBlend")->GetEffect()->End();
		EffectManager::GetInstance()->GetEffect("VertexBlend")->SetActive(false);



		/************************************************************************/
		/* Render all the billboards                                                                     */
		/************************************************************************/

		Matrix billboard;
		MatrixInverse( &billboard, NULL, &CameraController::GetInstance()->GetView() );
		billboard._41 = 0;
		billboard._42 = 0;
		billboard._43 = 0;

		Matrix world;
		MatrixIdentity(&world);
		EffectManager::GetInstance()->GetEffect("Billboard")->SetMatrix("m_WVP",world * CameraController::GetInstance()->GetView() * CameraController::GetInstance()->GetProjection());
		EffectManager::GetInstance()->GetEffect("Billboard")->SetMatrix("m_InvView", billboard);

		EffectManager::GetInstance()->GetEffect("Billboard")->GetEffect()->CommitChanges();
		numPasses = 0;
		EffectManager::GetInstance()->GetEffect("Billboard")->SetTechnique("mTech");
		EffectManager::GetInstance()->GetEffect("Billboard")->SetActive(true);
		EffectManager::GetInstance()->GetEffect("Billboard")->GetEffect()->Begin(&numPasses,0);
		EffectManager::GetInstance()->GetEffect("Billboard")->GetEffect()->BeginPass(0);
		RecursiveRender(m_firstEvent, RenderEvent::BillboardEffect);
		EffectManager::GetInstance()->GetEffect("Billboard")->GetEffect()->EndPass();
		EffectManager::GetInstance()->GetEffect("Billboard")->GetEffect()->End();
		EffectManager::GetInstance()->GetEffect("Billboard")->SetActive(false);
	
		EffectManager::GetInstance()->GetEffect("NormalMapEffect")->SetVector3("m_EyePosition", CameraController::GetInstance()->GetCurrentCameraPosition());
		EffectManager::GetInstance()->GetEffect("NormalMapEffect")->SetVector3("m_LightDirection",Vector3D(-1, 0.75f,0.1f));
		EffectManager::GetInstance()->GetEffect("NormalMapEffect")->SetInt("m_UVMultiply",1);
		EffectManager::GetInstance()->GetEffect("NormalMapEffect")->SetMatrix("m_View",CameraController::GetInstance()->GetView());
		EffectManager::GetInstance()->GetEffect("NormalMapEffect")->SetMatrix("m_Projection",CameraController::GetInstance()->GetProjection());

		EffectManager::GetInstance()->GetEffect("NormalMapEffect")->SetTechnique("mTech");
		EffectManager::GetInstance()->GetEffect("NormalMapEffect")->SetActive(true);
		EffectManager::GetInstance()->GetEffect("NormalMapEffect")->GetEffect()->Begin(&numPasses,0);
		EffectManager::GetInstance()->GetEffect("NormalMapEffect")->GetEffect()->BeginPass(0);
		

		RecursiveRender(m_firstEvent, RenderEvent::AmibentEnviroment);

		EffectManager::GetInstance()->GetEffect("NormalMapEffect")->GetEffect()->EndPass();
		EffectManager::GetInstance()->GetEffect("NormalMapEffect")->GetEffect()->End();
		EffectManager::GetInstance()->GetEffect("NormalMapEffect")->SetActive(false);
		
		RecursiveRender(m_firstEvent, RenderEvent::NoEffects);
	}
}

void
RenderManager::RecursiveRender(RenderEvent* e, RenderEvent::RenderFlag renderFlag)
{
	m_current = renderFlag;

	if (e->GetFlag(renderFlag))
	{
		e->Render();
	}

	if (e->m_firstChild)
	{
		RecursiveRender(e->m_firstChild, renderFlag);
	}

	if (e->m_nextSibling)
	{
		RecursiveRender(e->m_nextSibling, renderFlag);
	}
}

void 
RenderManager::RenderEnvironment()
{
	RecursiveRender(m_firstEvent, RenderEvent::AmibentEnviroment);
}

const RenderEvent::RenderFlag 
RenderManager::CurrentRenderFlag()
{
	return m_current;
}
