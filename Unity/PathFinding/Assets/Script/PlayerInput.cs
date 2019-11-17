using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class PlayerInput : MonoBehaviour {

    private Transform node;
    private Transform startNode;
    private Transform endNode;
    private List<Transform> blockPath = new List<Transform>();
    public GenerateGrid generateGrid;
    public bool moveStart,moveEnd = false;
    public InputField weight;

    private void Start()
    {
        generateGrid = FindObjectOfType<GenerateGrid>();
        startNode = generateGrid.grid[0];
        endNode = generateGrid.grid[generateGrid.grid.Count-1];
        updateNodeColor();
    }

    void Update () {
        mouseInput();
    }
    
    private void mouseInput()
    {
        if (Input.GetMouseButton(0))
        {
            this.colorBlockPath();
            this.updateNodeColor();

            Vector3 mousePos = Input.mousePosition;
            mousePos.z = 10;
            Vector3 screenPos = Camera.main.ScreenToWorldPoint(mousePos);
            RaycastHit2D hit = Physics2D.Raycast(screenPos, Vector2.zero);

            if (hit.collider != null && hit.transform.tag == "Node")
            {
                Renderer rend;
                if((moveEnd || moveStart )&& hit.transform != node)
                {
                    rend = node.GetComponent<Renderer>();
                    rend.material.color = Color.white;
                }                
                
                node = hit.transform;
                rend = node.GetComponent<Renderer>();

                if (node == startNode)
                {
                    moveStart = true;
                }
                else if (node == endNode)
                {
                    moveEnd = true;
                }

                Node n = node.GetComponent<Node>();
                if(n.getType() == TYPE.EMPTY && !moveStart && !moveEnd)
                {
                    rend.material.color = Color.blue;
                    n.setType(TYPE.BLOCK);
                    n.setWalkable(false);
                    blockPath.Add(node);
                }

                if(moveStart)
                {
                    startNode = node;
                }
                else if(moveEnd)
                {
                    endNode = node;
                }
            }
        }
        if (Input.GetMouseButton(1))
        {
            this.colorBlockPath();

            Vector3 mousePos = Input.mousePosition;
            mousePos.z = 10;
            Vector3 screenPos = Camera.main.ScreenToWorldPoint(mousePos);
            RaycastHit2D hit = Physics2D.Raycast(screenPos, Vector2.zero);

            if (hit.collider != null && hit.transform.tag == "Node")
            {
                Renderer rend;
                node = hit.transform;
                rend = node.GetComponent<Renderer>();

                Node n = node.GetComponent<Node>();
                if (n.getType() == TYPE.BLOCK)
                {
                    rend.material.color = Color.white;
                    n.setType(TYPE.EMPTY);
                    n.setWalkable(true);
                    blockPath.Remove(node);
                }
            }
        }
        if(Input.GetMouseButtonUp(0))
        {
            moveStart = false;
            moveEnd = false;
            updateNodeColor();
        }
    }

    public void btnDijkstrasPath()
    {   
        if (startNode != null && endNode != null)
        {
            ShortestPath finder = gameObject.GetComponent<ShortestPath>();
            List<Transform> paths = finder.DijkstrasPath(startNode, endNode);

            foreach (Transform path in paths)
            {
                Renderer rend = path.GetComponent<Renderer>();
                rend.material.color = Color.yellow;
            }
        }
    }

    public void btnAStar()
    {
        if (startNode != null && endNode != null)
        {
            ShortestPath finder = gameObject.GetComponent<ShortestPath>();
            Debug.Log(weight.text);
            List<Transform> paths = finder.aStarPath(startNode, endNode,System.Convert.ToInt32(weight.text));

            foreach (Transform path in paths)
            {
                Renderer rend = path.GetComponent<Renderer>();
                rend.material.color = Color.yellow;
            }
        }
    }

    public void btnClearBlock()
    {   
        // For each blocked path in the list
        foreach(Transform path in blockPath)
        {   
            // Set walkable to true.
            Node n = path.GetComponent<Node>();
            n.setWalkable(true);

            // Set their color to white.
            Renderer rend = path.GetComponent<Renderer>();
            rend.material.color = Color.white;

        }
        // Clear the block path list and 
        blockPath.Clear();
    }

    public void btnRestart()
    {
        Scene loadedLevel = SceneManager.GetActiveScene();
        SceneManager.LoadScene(loadedLevel.buildIndex);
    }

    private void colorBlockPath()
    {
        foreach(Transform block in blockPath)
        {
            Renderer rend = block.GetComponent<Renderer>();
            rend.material.color = Color.blue;
        }
    }

    private void updateNodeColor()
    {
        if (startNode != null)
        {
            Renderer rend = startNode.GetComponent<Renderer>();
            rend.material.color = Color.green;
        }

        if (endNode != null)
        {
            Renderer rend = endNode.GetComponent<Renderer>();
            rend.material.color = Color.red;
        }
    }

}
