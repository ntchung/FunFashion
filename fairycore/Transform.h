#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include "maths/Vector3f.h"
#include "maths/Quaternion.h"
#include "maths/Matrix4x4.h"
#include "utils/SharedObject.h"

class Transform : public SharedObject
{
public:
	static Transform* create(Transform* parent = NULL);
	virtual void destroy();

	enum Space
	{
		Self = 0,
		World
	};	
	
	//
	// Properties
	//
	int childCount() const;	

	inline Vector3f eulerAngles()
	{		
		return this->rotation().eulerAngles();
	}

	inline void setEulerAngles(const Vector3f& value)
	{
		this->setRotation(Quaternion::Euler(value));
	}

	inline Vector3f forward() const
	{
		return this->rotation() * Vector3f::forward;
	}

	inline void setForward(const Vector3f& value)
	{
		this->setRotation(Quaternion::LookRotation(value));
	}	

	bool hasChanged() const;
	void setHasChanged(bool value);
	
	Vector3f localEulerAngles() const;
	void setLocalEulerAngles(const Vector3f& value);
	
	Vector3f localPosition() const;
	void setLocalPosition(const Vector3f& value);
	
	Quaternion localRotation() const;
	void setLocalRotation(const Quaternion& value);
	void transformLocalRotation(const Quaternion& value);
	
	inline Vector3f localScale() const { return m_scale; }
	inline void setLocalScale(const Vector3f& value) { m_scale = value; m_isIdentity = false; }
	
	inline Matrix4x4 localToWorldMatrix() const { return m_worldMatrix; }
	
	Vector3f lossyScale() const;

	Transform* parent() const;
	void setParent(Transform* parent);

	Vector3f position() const;
	void setPosition(const Vector3f& pos);
	void translatePosition(const Vector3f& pos);
		
	inline Vector3f right() const
	{
		return this->rotation() * Vector3f::right;
	}
		
	void setRight(const Vector3f& value)
	{
		this->setRotation(Quaternion::FromToRotation(Vector3f::right, value));
	}
	
	Transform* root() const;
	
	Quaternion rotation() const;
	void setRotation(const Quaternion& value);
	void transformRotation(const Quaternion& value);

	inline Vector3f up() const
	{
		return this->rotation() * Vector3f::up;
	}

	inline void setUp(const Vector3f& value)
	{	
		this->setRotation(Quaternion::FromToRotation(Vector3f::up, value));
	}

	inline Matrix4x4 worldToLocalMatrix() const { return m_localMatrix; }
	
	//
	// Methods
	//
	void DetachChildren();	
	Transform* FindChild(const char* name);
	Transform* GetChild(int index);

	Vector3f InverseTransformDirection(const Vector3f& direction);	
	Vector3f InverseTransformDirection(float x, float y, float z);	
	Vector3f InverseTransformPoint(float x, float y, float z);
	Vector3f InverseTransformPoint(const Vector3f& position);
	
	bool IsChildOf(Transform* parent);

	inline void LookAt(Transform* target, const Vector3f& worldUp = Vector3f::up)
	{
		this->LookAt(target->position(), worldUp);
	}
	
	void LookAt(const Vector3f& worldPosition, const Vector3f& worldUp = Vector3f::up)
	{
		// TODO
	}

	inline void Rotate(float xAngle, float yAngle, float zAngle)
	{
		Space relativeTo = Self;
		this->Rotate(xAngle, yAngle, zAngle, relativeTo);
	}

	inline void Rotate(const Vector3f& eulerAngles)
	{
		Space relativeTo = Self;
		this->Rotate(eulerAngles, relativeTo);
	}

	inline void Rotate(float xAngle, float yAngle, float zAngle, Space relativeTo = Self)
	{
		this->Rotate(Vector3f(xAngle, yAngle, zAngle), relativeTo);
	}

	inline void Rotate(const Vector3f& eulerAngles, Space relativeTo = Self)
	{
		Quaternion rhs = Quaternion::Euler(eulerAngles.x, eulerAngles.y, eulerAngles.z);
		if (relativeTo == Self)
		{
			this->transformLocalRotation(rhs);
		}
		else
		{
			this->transformRotation(Quaternion::Inverse(this->rotation()) * rhs * this->rotation());
		}
	}

	inline void Rotate(const Vector3f& axis, float angle, Space relativeTo = Self)
	{
		// TODO
		if (relativeTo == Self)
		{
			//this->RotateAroundInternal(base.transform.TransformDirection(axis), angle * 0.0174532924f);
		}
		else
		{
			//this->RotateAroundInternal(axis, angle * 0.0174532924f);
		}
	}
	
	inline void Rotate(const Vector3f& axis, float angle)
	{
		Space relativeTo = Self;
		this->Rotate(axis, angle, relativeTo);
	}

	inline void RotateAround(const Vector3f& point, const Vector3f& axis, float angle)
	{
		Vector3f vector = this->position();
		Quaternion rotation = Quaternion::AngleAxis(angle, axis);
		Vector3f vector2 = vector - point;
		vector2 = rotation * vector2;
		vector = point + vector2;
		this->setPosition(vector);

		// TODO
		//this->RotateAroundInternal(axis, angle * Mathf::Deg2Rad);
	}

	inline Vector3f TransformDirection(const Vector3f& direction)
	{
		// TODO
		return Vector3f();
	}

	inline Vector3f TransformDirection(float x, float y, float z)
	{
		// TODO
		return Vector3f();
	}

	inline Vector3f TransformPoint(float x, float y, float z)
	{
		return this->TransformPoint(Vector3f(x, y, z));
	}

	inline Vector3f TransformPoint(const Vector3f& position)
	{
		// TODO
		return Vector3f();
	}

	void TransformPoints(float* positions, int size);
	
	inline void Translate(const Vector3f& translation, Space relativeTo = Self)
	{
		if (relativeTo == World)
		{
			this->translatePosition(translation);
		}
		else
		{
			this->translatePosition(this->TransformDirection(translation));
		}
	}

	inline void Translate(const Vector3f& translation, Transform* relativeTo)
	{
		this->translatePosition(relativeTo->TransformDirection(translation));
	}

	inline void Translate(const Vector3f& translation)
	{
		translatePosition(translation);
	}

	inline void Translate(float x, float y, float z, Transform* relativeTo)
	{
		this->Translate(Vector3f(x, y, z), relativeTo);
	}

	inline void Translate(float x, float y, float z, Space relativeTo = Self)
	{
		this->Translate(Vector3f(x, y, z), relativeTo);
	}

	// Engine use
	static void setup();
	static void update();	

private:
	Transform();
	Transform(Transform* parent);
	~Transform();

	Transform* m_parent;
	Transform* m_firstChild;
	Transform* m_nextSibling;

	Quaternion m_rotation;
	Vector3f m_position;
	Vector3f m_scale;

	Matrix4x4 m_worldMatrix;
	Matrix4x4 m_localMatrix;

	static void update(Transform* root);
	
	void UpdateMatrix();

	bool m_isIdentity;
};

#endif // __TRANSFORM_H__
