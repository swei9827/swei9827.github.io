using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PixelCollider : MonoBehaviour {

    [HideInInspector] public SpriteRenderer spr;
    [SerializeField] public PixelCollider[] other;
    bool hasCollision = false;
    public Rect preview;
    public Color[] colorPreview = new Color[1000];
    public float collideTime;
	// Use this for initialization
	void Start () {
        collideTime = 0;
        this.spr = GetComponent<SpriteRenderer>();	
	}

    // Update is called once per frame
    void Update () {
        checkCollision();
        ShowFeedback();
	}
    void checkCollision()
    {
        for(int i=0;i<other.Length;i++)
        {
            if (this.spr.bounds.Intersects(other[i].spr.bounds))
            {
                //1.Get global intersection 
                Rect globalInt = new Rect();
                globalInt.xMin = Mathf.Max(this.spr.bounds.min.x, other[i].spr.bounds.min.x);
                globalInt.xMax = Mathf.Min(this.spr.bounds.max.x, other[i].spr.bounds.max.x);
                globalInt.yMin = Mathf.Max(this.spr.bounds.min.y, other[i].spr.bounds.min.y);
                globalInt.yMax = Mathf.Min(this.spr.bounds.max.y, other[i].spr.bounds.max.y);
                preview = globalInt;
                //2.Convert to this local intersection 
                Rect localSect = new Rect();
                localSect.xMin = globalInt.xMin - this.spr.bounds.min.x;
                localSect.yMin = globalInt.yMin - this.spr.bounds.min.y;
                localSect.width = globalInt.width;
                localSect.height = globalInt.height;
                //3.Get other sprite's local intersection 
                Rect OtherSect = new Rect();
                OtherSect.xMin = globalInt.xMin - other[i].spr.bounds.min.x;
                OtherSect.yMin = globalInt.yMin - other[i].spr.bounds.min.y;
                OtherSect.width = globalInt.width;
                OtherSect.height = globalInt.height;
                //4.Get This sprite's Color array
                Color[] localColor = this.spr.sprite.texture.GetPixels(Mathf.RoundToInt(localSect.xMin),
                    Mathf.RoundToInt(localSect.yMin),
                    Mathf.RoundToInt(localSect.width),
                    Mathf.RoundToInt(localSect.height));
                this.colorPreview = localColor;
                //5.Get other sprite Color array
                Color[] otherColor = other[i].spr.sprite.texture.GetPixels(Mathf.RoundToInt(OtherSect.xMin),
                    Mathf.RoundToInt(OtherSect.yMin),
                    Mathf.RoundToInt(OtherSect.width),
                    Mathf.RoundToInt(OtherSect.height));
                //6.Compare both color arrays in a for loop
                for (int j = 0; j < localColor.Length && j < otherColor.Length; j++)
                {
                    //7.Check for collision!
                    if (localColor[j].a == 1f && otherColor[j].a == 1f)
                    {
                        hasCollision = true;
                        return;
                    }
                }
                hasCollision = false;
            }
            else this.hasCollision = false;
        }
    }

    void ShowFeedback()
    {
        if (hasCollision)
        {
            collideTime += Time.deltaTime;
            if (collideTime < 0.5f)
            {
                this.spr.color = Color.red;
            }
            else if (collideTime >= 0.5f)
            {
                this.spr.color = Color.yellow;
            }
        }
        else
        {
            collideTime = 0;
            this.spr.color = Color.white;
        }
    }
}
