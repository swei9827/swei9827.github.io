using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Tile : MonoBehaviour {
    
    [Header("Sprite Stuff")]
    [SerializeField] SpriteRenderer spriteRenderer;

    public void RenderSprite( Sprite s)
    {
        this.spriteRenderer.sprite = s;
    }
}
