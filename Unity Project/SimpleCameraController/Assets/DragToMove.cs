using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DragToMove : MonoBehaviour {
    Vector3 lastPos = Vector3.zero;
    Vector3 deltaPosition = Vector3.zero;

    void Update () {
        Drag();
        Move();
	}

    void Drag()
    {
        //Reset to snapp all back to zero or normalized position
        if(Input.touchCount>0)
        {
            deltaPosition = Input.mousePosition - lastPos;
            lastPos = Input.mousePosition;
        }
    }

    void Move()
    {
        Vector3 direction = new Vector3(Input.GetTouch(0).deltaPosition.x, 0, Input.GetTouch(0).deltaPosition.y);

        this.transform.Translate(direction, Space.World);

        deltaPosition = Vector3.Lerp(deltaPosition, Vector3.zero, Time.deltaTime * 1f);
    }
}
