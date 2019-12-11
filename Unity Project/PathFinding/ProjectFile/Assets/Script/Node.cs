using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Node : MonoBehaviour {

    [SerializeField] private float gCost = int.MaxValue;
    [SerializeField] private float heuristic = 0;
    [SerializeField] private float fCost = int.MaxValue;
    [SerializeField] private Transform parentNode = null;
    [SerializeField] private List<Transform> neighbourNode;
    [SerializeField] private bool walkable = true;
    [SerializeField] private TYPE type = TYPE.EMPTY;

    // Use this for initialization
    void Start () {
        this.resetNode();
    }

    public void resetNode()
    {
        gCost = int.MaxValue;
        heuristic = 0;
        fCost = int.MaxValue;
        parentNode = null;
        this.GetComponent<SpriteRenderer>().material.color = Color.white;
    }

    public void setParentNode(Transform node)
    {
        this.parentNode = node;
    }

    public void setgCost(float value)
    {
        this.gCost = value;
    }

    public void setWalkable(bool b)
    {
        this.walkable = b;
    }

    public void addNeighbourNode(Transform node)
    {
        this.neighbourNode.Add(node);
    }

    public List<Transform> getNeighbourNode()
    {
        List<Transform> result = this.neighbourNode;
        return result;
    }

    public float getgCost()
    {
        float result = this.gCost;
        return result;
    }

    public float getHeuristic()
    {
        float result = this.heuristic;
        return result;
    }

    public void setHeuristic(float value)
    {
        this.heuristic = value;
    }

    public float getfCost()
    {
        float result = this.fCost;
        return result;
    }

    public void setfCost(float value)
    {
        this.fCost = value;
    }

    public Transform getParentNode()
    {
        Transform result = this.parentNode;
        return result;
    }

    public bool isWalkable()
    {
        bool result = walkable;
        return result;
    }

    public TYPE getType()
    {
        TYPE result = this.type;
        return result;
    }

    public void setType(TYPE t)
    {
        this.type = t;
    }
}

public enum TYPE
{
    EMPTY = 0,
    BLOCK,
    START,
    END
}
