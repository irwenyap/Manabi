#include "TransformSystem.h"

#include "../Source/Coordinator.h"

#include "../Components/Transform.hpp";


extern Coordinator g_coordinator;

void TransformSystem::Initialize() {
	for (auto const& entity : m_entities) {
		Mtx44 modelTrans, modelRot, modelRotX, modelRotY, modelRotZ, modelScale;
		auto& transform = g_coordinator.GetComponent<Transform>(entity);

		if (transform.parent) {
			modelTrans.SetToTranslation(transform.localPosition.x, transform.localPosition.y, transform.localPosition.z);

			modelRotX.SetToRotation(transform.rotation.x, 1, 0, 0);
			modelRotY.SetToRotation(transform.rotation.y, 0, 1, 0);
			modelRotZ.SetToRotation(transform.rotation.z, 0, 0, 1);
			modelRot = modelRotX * modelRotY * modelRotZ;

			modelScale.SetToScale(transform.localScale.x, transform.localScale.y, transform.localScale.z);
			transform.localToWorldMatrix = transform.parent->localToWorldMatrix * (modelTrans * modelRot * modelScale);
			transform.position = Vector3(transform.localToWorldMatrix.a[4], transform.localToWorldMatrix.a[8], transform.localToWorldMatrix.a[12]);
		} else {
			modelTrans.SetToTranslation(transform.position.x, transform.position.y, transform.position.z);

			modelRotX.SetToRotation(transform.rotation.x, 1, 0, 0);
			modelRotY.SetToRotation(transform.rotation.y, 0, 1, 0);
			modelRotZ.SetToRotation(transform.rotation.z, 0, 0, 1);
			modelRot = modelRotX * modelRotY * modelRotZ;

			modelScale.SetToScale(transform.scale.x, transform.scale.y, transform.scale.z);
			transform.localToWorldMatrix = modelTrans * modelRot * modelScale;
		}
	}
}

void TransformSystem::Update(double dt) {
	for (auto const& entity : m_entities) {
		Mtx44 modelTrans, modelRot, modelRotX, modelRotY, modelRotZ, modelScale;
		auto& transform = g_coordinator.GetComponent<Transform>(entity);

		if (transform.parent) {
			modelTrans.SetToTranslation(transform.localPosition.x, transform.localPosition.y, transform.localPosition.z);


			modelRotX.SetToRotation(transform.rotation.x, 1, 0, 0);
			modelRotY.SetToRotation(transform.rotation.y, 0, 1, 0);
			modelRotZ.SetToRotation(transform.rotation.z, 0, 0, 1);
			modelRot = modelRotX * modelRotY * modelRotZ;

			modelScale.SetToScale(transform.localScale.x, transform.localScale.y, transform.localScale.z);
			transform.localToWorldMatrix = transform.parent->localToWorldMatrix * (modelTrans * modelRot * modelScale);
			transform.position = Vector3(transform.localToWorldMatrix.a[13], transform.localToWorldMatrix.a[14], transform.localToWorldMatrix.a[15]);
		} else {
			modelTrans.SetToTranslation(transform.position.x, transform.position.y, transform.position.z);

			modelRotX.SetToRotation(transform.rotation.x, 1, 0, 0);
			modelRotY.SetToRotation(transform.rotation.y, 0, 1, 0);
			modelRotZ.SetToRotation(transform.rotation.z, 0, 0, 1);
			modelRot = modelRotX * modelRotY * modelRotZ;

			modelScale.SetToScale(transform.scale.x, transform.scale.y, transform.scale.z);
			transform.localToWorldMatrix = modelTrans * modelRot * modelScale;
		}
	}
	ConvertWorldToLocalMatrix();
}

void TransformSystem::Exit() {
	for (auto const& entity : m_entities) {
		Transform& transform = g_coordinator.GetComponent<Transform>(entity);
		//if (transform.parent != nullptr)
		//	delete(transform.parent);
		transform.parent = NULL;
	}
}

void TransformSystem::ConvertWorldToLocalMatrix() {
	for (auto const& entity : m_entities) {
		auto& transform = g_coordinator.GetComponent<Transform>(entity);
		if (transform.parent) {
			Mtx44 modelTrans, modelRot, modelScale;



			//transform.worldToLocalMatrix = transform.localToWorldMatrix * transform.parent->localToWorldMatrix.GetInverse();


			//if (transform.parent) {
			//	modelTrans.SetToTranslation(transform.position.x, transform.position.y, transform.position.z);
			//	modelRot.SetToIdentity();
			//	modelScale.SetToScale(transform.scale.x, transform.scale.y, transform.scale.z);
			//	transform.localToWorldMatrix = transform.parent->localToWorldMatrix * (modelTrans * modelRot * modelScale);
			//} else {
			//	modelTrans.SetToTranslation(transform.position.x, transform.position.y, transform.position.z);
			//	modelRot.SetToIdentity();
			//	modelScale.SetToScale(transform.scale.x, transform.scale.y, transform.scale.z);
			//	transform.localToWorldMatrix = modelTrans * modelRot * modelScale;
			//}
		}
	}
}
