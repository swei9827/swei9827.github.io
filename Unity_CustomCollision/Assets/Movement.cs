using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Movement : MonoBehaviour {
    public bool useDefault;
    public string up;
    public string down;
    public string left;
    public string right;

    // Update is called once per frame
    void Update () {
        if(useDefault)
        {
            if (Input.GetKeyDown(KeyCode.LeftArrow)) transform.Translate(Vector2.left);
            if (Input.GetKeyDown(KeyCode.RightArrow)) transform.Translate(Vector2.right);
            if (Input.GetKeyDown(KeyCode.UpArrow)) transform.Translate(Vector2.up);
            if (Input.GetKeyDown(KeyCode.DownArrow)) transform.Translate(Vector2.down);
        }
        else
        {
            if (Input.GetKeyDown(left)) transform.Translate(Vector2.left);
            if (Input.GetKeyDown(right)) transform.Translate(Vector2.right);
            if (Input.GetKeyDown(up)) transform.Translate(Vector2.up);
            if (Input.GetKeyDown(down)) transform.Translate(Vector2.down);
        }
    }
}
