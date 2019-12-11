using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IKController : MonoBehaviour {

    Animator anim;
    public Transform target;
    public Transform leftHandHint;
    public float leftHandWeight = 0f;

	void Start () {
        anim = GetComponent<Animator>();	
	}

    public void OnAnimatorIK(int layerIndex)
    {
        anim.SetIKPosition(AvatarIKGoal.LeftHand, target.position);
        anim.SetIKPositionWeight(AvatarIKGoal.LeftHand, leftHandWeight);

        anim.SetIKHintPosition(AvatarIKHint.LeftElbow, leftHandHint.position);
        anim.SetIKHintPositionWeight(AvatarIKHint.LeftElbow, 1f);

        anim.SetLookAtPosition(target.position);
        anim.SetLookAtWeight(1f);
    }
}
