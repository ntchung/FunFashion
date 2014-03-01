#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include "maths/Vector3f.h"

struct Transform
{
public:
	/*
	//
	// Properties
	//
	int childCount() const;	

	public Vector3 eulerAngles
	{
		get
		{
		return this.rotation.eulerAngles;
	}
		set
		{
			this.rotation = Quaternion.Euler(value);
		}
	}

	public Vector3 forward
	{
		get
		{
		return this.rotation * Vector3.forward;
	}
		set
		{
			this.rotation = Quaternion.LookRotation(value);
		}
	}

	public extern bool hasChanged
	{
		[WrapperlessIcall]
		[MethodImpl(MethodImplOptions.InternalCall)]
		get;
		[WrapperlessIcall]
		[MethodImpl(MethodImplOptions.InternalCall)]
		set;
	}

	public Vector3 localEulerAngles
	{
		get
		{
		Vector3 result;
		this.INTERNAL_get_localEulerAngles(out result);
		return result;
	}
		set
		{
			this.INTERNAL_set_localEulerAngles(ref value);
		}
	}

	public Vector3 localPosition
	{
		get
		{
		Vector3 result;
		this.INTERNAL_get_localPosition(out result);
		return result;
	}
		set
		{
			this.INTERNAL_set_localPosition(ref value);
		}
	}

	public Quaternion localRotation
	{
		get
		{
		Quaternion result;
		this.INTERNAL_get_localRotation(out result);
		return result;
	}
		set
		{
			this.INTERNAL_set_localRotation(ref value);
		}
	}

	public Vector3 localScale
	{
		get
		{
		Vector3 result;
		this.INTERNAL_get_localScale(out result);
		return result;
	}
		set
		{
			this.INTERNAL_set_localScale(ref value);
		}
	}

	public Matrix4x4 localToWorldMatrix
	{
		get
		{
		Matrix4x4 result;
		this.INTERNAL_get_localToWorldMatrix(out result);
		return result;
	}
	}

	public Vector3 lossyScale
	{
		get
		{
		Vector3 result;
		this.INTERNAL_get_lossyScale(out result);
		return result;
	}
	}

	public extern Transform parent
	{
		[WrapperlessIcall]
		[MethodImpl(MethodImplOptions.InternalCall)]
		get;
		[WrapperlessIcall]
		[MethodImpl(MethodImplOptions.InternalCall)]
		set;
	}

	public Vector3 position
	{
		get
		{
		Vector3 result;
		this.INTERNAL_get_position(out result);
		return result;
	}
		set
		{
			this.INTERNAL_set_position(ref value);
		}
	}

	public Vector3 right
	{
		get
		{
		return this.rotation * Vector3.right;
	}
		set
		{
			this.rotation = Quaternion.FromToRotation(Vector3.right, value);
		}
	}

	public extern Transform root
	{
		[WrapperlessIcall]
		[MethodImpl(MethodImplOptions.InternalCall)]
		get;
	}

	public Quaternion rotation
	{
		get
		{
		Quaternion result;
		this.INTERNAL_get_rotation(out result);
		return result;
	}
		set
		{
			this.INTERNAL_set_rotation(ref value);
		}
	}

	public Vector3 up
	{
		get
		{
		return this.rotation * Vector3.up;
	}
		set
		{
			this.rotation = Quaternion.FromToRotation(Vector3.up, value);
		}
	}

	public Matrix4x4 worldToLocalMatrix
	{
		get
		{
		Matrix4x4 result;
		this.INTERNAL_get_worldToLocalMatrix(out result);
		return result;
	}
	}

	//
	// Methods
	//
	[WrapperlessIcall]
	[MethodImpl(MethodImplOptions.InternalCall)]
	public extern void DetachChildren();

	[WrapperlessIcall]
	[MethodImpl(MethodImplOptions.InternalCall)]
	public extern Transform Find(string name);

	public Transform FindChild(string name)
	{
		return this.Find(name);
	}

	[WrapperlessIcall]
	[MethodImpl(MethodImplOptions.InternalCall)]
	public extern Transform GetChild(int index);

	[Obsolete("use Transform.childCount instead."), WrapperlessIcall]
	[MethodImpl(MethodImplOptions.InternalCall)]
	public extern int GetChildCount();

	public IEnumerator GetEnumerator()
	{
		return new Transform.Enumerator(this);
	}

	public Vector3 InverseTransformDirection(Vector3 direction)
	{
		return Transform.INTERNAL_CALL_InverseTransformDirection(this, ref direction);
	}

	public Vector3 InverseTransformDirection(float x, float y, float z)
	{
		return this.InverseTransformDirection(new Vector3(x, y, z));
	}

	public Vector3 InverseTransformPoint(float x, float y, float z)
	{
		return this.InverseTransformPoint(new Vector3(x, y, z));
	}

	public Vector3 InverseTransformPoint(Vector3 position)
	{
		return Transform.INTERNAL_CALL_InverseTransformPoint(this, ref position);
	}

	[WrapperlessIcall]
	[MethodImpl(MethodImplOptions.InternalCall)]
	public extern bool IsChildOf(Transform parent);

	public void LookAt(Transform target, [DefaultValue("Vector3.up")] Vector3 worldUp)
	{
		if (target)
		{
			this.LookAt(target.position, worldUp);
		}
	}

	[ExcludeFromDocs]
	public void LookAt(Transform target)
	{
		Vector3 up = Vector3.up;
		this.LookAt(target, up);
	}

	[ExcludeFromDocs]
	public void LookAt(Vector3 worldPosition)
	{
		Vector3 up = Vector3.up;
		Transform.INTERNAL_CALL_LookAt(this, ref worldPosition, ref up);
	}

	public void LookAt(Vector3 worldPosition, [DefaultValue("Vector3.up")] Vector3 worldUp)
	{
		Transform.INTERNAL_CALL_LookAt(this, ref worldPosition, ref worldUp);
	}

	[ExcludeFromDocs]
	public void Rotate(float xAngle, float yAngle, float zAngle)
	{
		Space relativeTo = Space.Self;
		this.Rotate(xAngle, yAngle, zAngle, relativeTo);
	}

	[ExcludeFromDocs]
	public void Rotate(Vector3 eulerAngles)
	{
		Space relativeTo = Space.Self;
		this.Rotate(eulerAngles, relativeTo);
	}

	public void Rotate(float xAngle, float yAngle, float zAngle, [DefaultValue("Space.Self")] Space relativeTo)
	{
		this.Rotate(new Vector3(xAngle, yAngle, zAngle), relativeTo);
	}

	public void Rotate(Vector3 eulerAngles, [DefaultValue("Space.Self")] Space relativeTo)
	{
		Quaternion rhs = Quaternion.Euler(eulerAngles.x, eulerAngles.y, eulerAngles.z);
		if (relativeTo == Space.Self)
		{
			this.localRotation *= rhs;
		}
		else
		{
			this.rotation *= Quaternion.Inverse(this.rotation) * rhs * this.rotation;
		}
	}

	public void Rotate(Vector3 axis, float angle, [DefaultValue("Space.Self")] Space relativeTo)
	{
		if (relativeTo == Space.Self)
		{
			this.RotateAroundInternal(base.transform.TransformDirection(axis), angle * 0.0174532924f);
		}
		else
		{
			this.RotateAroundInternal(axis, angle * 0.0174532924f);
		}
	}

	[ExcludeFromDocs]
	public void Rotate(Vector3 axis, float angle)
	{
		Space relativeTo = Space.Self;
		this.Rotate(axis, angle, relativeTo);
	}

	public void RotateAround(Vector3 point, Vector3 axis, float angle)
	{
		Vector3 vector = this.position;
		Quaternion rotation = Quaternion.AngleAxis(angle, axis);
		Vector3 vector2 = vector - point;
		vector2 = rotation * vector2;
		vector = point + vector2;
		this.position = vector;
		this.RotateAroundInternal(axis, angle * 0.0174532924f);
	}

	[Obsolete("use Transform.Rotate instead.")]
	public void RotateAround(Vector3 axis, float angle)
	{
		Transform.INTERNAL_CALL_RotateAround(this, ref axis, angle);
	}

	[Obsolete("use Transform.Rotate instead.")]
	public void RotateAroundLocal(Vector3 axis, float angle)
	{
		Transform.INTERNAL_CALL_RotateAroundLocal(this, ref axis, angle);
	}

	public Vector3 TransformDirection(Vector3 direction)
	{
		return Transform.INTERNAL_CALL_TransformDirection(this, ref direction);
	}

	public Vector3 TransformDirection(float x, float y, float z)
	{
		return this.TransformDirection(new Vector3(x, y, z));
	}

	public Vector3 TransformPoint(float x, float y, float z)
	{
		return this.TransformPoint(new Vector3(x, y, z));
	}

	public Vector3 TransformPoint(Vector3 position)
	{
		return Transform.INTERNAL_CALL_TransformPoint(this, ref position);
	}

	public void Translate(Vector3 translation, [DefaultValue("Space.Self")] Space relativeTo)
	{
		if (relativeTo == Space.World)
		{
			this.position += translation;
		}
		else
		{
			this.position += this.TransformDirection(translation);
		}
	}

	[ExcludeFromDocs]
	public void Translate(Vector3 translation)
	{
		Space relativeTo = Space.Self;
		this.Translate(translation, relativeTo);
	}

	public void Translate(Vector3 translation, Transform relativeTo)
	{
		if (relativeTo)
		{
			this.position += relativeTo.TransformDirection(translation);
		}
		else
		{
			this.position += translation;
		}
	}

	public void Translate(float x, float y, float z, Transform relativeTo)
	{
		this.Translate(new Vector3(x, y, z), relativeTo);
	}

	[ExcludeFromDocs]
	public void Translate(float x, float y, float z)
	{
		Space relativeTo = Space.Self;
		this.Translate(x, y, z, relativeTo);
	}

	public void Translate(float x, float y, float z, [DefaultValue("Space.Self")] Space relativeTo)
	{
		this.Translate(new Vector3(x, y, z), relativeTo);
	}
*/
};

#endif // __TRANSFORM_H__
