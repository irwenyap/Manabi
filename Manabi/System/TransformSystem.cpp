#include "TransformSystem.h"

#include "../Source/Coordinator.h"

#include "../Components/Transform.hpp";


extern Coordinator g_coordinator;

void TransformSystem::Initialize() {
	for (auto const& entity : m_entities) {
		Mtx44 modelTrans, modelRot, modelScale;
		auto& transform = g_coordinator.GetComponent<Transform>(entity);

		if (transform.parent) {
			modelTrans.SetToTranslation(transform.position.x, transform.position.y, transform.position.z);
			modelRot.SetToIdentity();
			modelScale.SetToScale(transform.scale.x, transform.scale.y, transform.scale.z);
			transform.localToWorldMatrix = transform.parent->localToWorldMatrix * (modelScale * modelRot * modelTrans);
		} else {
			modelTrans.SetToTranslation(transform.position.x, transform.position.y, transform.position.z);
			modelRot.SetToIdentity();
			modelScale.SetToScale(transform.scale.x, transform.scale.y, transform.scale.z);
			transform.localToWorldMatrix = modelScale * modelRot * modelTrans;
		}
	}
}

void TransformSystem::Update(double dt) {
	for (auto const& entity : m_entities) {
		//Mtx44 modelTrans, modelRot, modelScale;
		//auto transform = g_coordinator.GetComponent<Transform>(entity);

		//modelTrans.SetToTranslation(transform.position.x, transform.position.y, transform.position.z);
		//modelRot.SetToIdentity();
		//modelScale.SetToScale(transform.scale.x, transform.scale.y, transform.scale.z);
		//transform.localToWorldMatrix = modelTrans * modelRot * modelScale;
	}
}

void TransformSystem::Exit() {
}