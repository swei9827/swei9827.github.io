using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TapToFocus : MonoBehaviour {

    Vector3 offset;
    Vector3 targetPos;

    private void Start()
    {
        GetOffset();
        targetPos = this.transform.position;
    }

    void Update ()
    {
        if(Input.GetMouseButtonDown(0))GetTargetPosition();
        MoveToTargetPostion();
    }

    void GetTargetPosition()
    {
        if(Input.touchCount > 0)
        {
            Ray ray = Camera.main.ScreenPointToRay(Input.GetTouch(0).position);
            RaycastHit hitInfo;

            if(Physics.Raycast(ray,out hitInfo) == true)
            {
                Debug.Log(hitInfo.point);
                targetPos = hitInfo.point + offset;
            }
        }
    }

    void GetOffset()
    {
        Vector3 centerPoint = Vector3.zero;
        centerPoint.x = (float)Screen.width / 2f;
        centerPoint.y = (float)Screen.height / 2f;

        Ray ray = Camera.main.ScreenPointToRay(centerPoint);
        RaycastHit hitInfo;

        if (Physics.Raycast(ray, out hitInfo) == true)
        {
            offset = this.transform.position - hitInfo.point;
        }

    }

    void MoveToTargetPostion()
    {
        this.transform.position = Vector3.MoveTowards(transform.position, targetPos, Time.deltaTime*100f );
    }

    private void Drag()
    {
        //Input.GetTouch(0).deltaPosition.magnitude
        this.transform.Translate(Input.GetTouch(0).deltaPosition.x, 0, Input.GetTouch(0).deltaPosition.y);
    }
}
