using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ShortestPath : MonoBehaviour
{
    private GameObject[] nodes;

    public List<Transform> DijkstrasPath(Transform start, Transform end)
    {
        nodes = GameObject.FindGameObjectsWithTag("Node");

        List<Transform> result = new List<Transform>();
        Transform node = DijkstrasAlgo(start, end);       

        while (node != null)
        {
            result.Add(node);
            Node currentNode = node.GetComponent<Node>();
            node = currentNode.getParentNode();
        }
        
        result.Reverse();
        return result;
    }

    public List<Transform> aStarPath(Transform start, Transform end, int weight)
    {
        nodes = GameObject.FindGameObjectsWithTag("Node");

        List<Transform> result = new List<Transform>();
        Transform node = aStar(start, end,weight);

        while (node != null)
        {
            result.Add(node);
            Node currentNode = node.GetComponent<Node>();
            node = currentNode.getParentNode();
        }

        result.Reverse();
        return result;
    }

    private Transform DijkstrasAlgo(Transform start, Transform end)
    {
        List<Transform> unexplored = new List<Transform>();

        foreach (GameObject obj in nodes)
        {
            Node n = obj.GetComponent<Node>();
            if (n.isWalkable())
            {
                n.resetNode();
                unexplored.Add(obj.transform);
            }
        }

        Node startNode = start.GetComponent<Node>();
        startNode.setgCost(0);

        while (unexplored.Count > 0)
        {
            // Sort the explored by their weight in ascending order.
            unexplored.Sort((x, y) => x.GetComponent<Node>().getgCost().CompareTo(y.GetComponent<Node>().getgCost()));

            Transform current = unexplored[0];

            if(current == end)
            {   
                return end;
            }

            unexplored.Remove(current);

            Node currentNode = current.GetComponent<Node>();
            List<Transform> neighbours = currentNode.getNeighbourNode();
            foreach (Transform neighNode in neighbours)
            {                
                Node node = neighNode.GetComponent<Node>();

                if (unexplored.Contains(neighNode) && node.isWalkable())
                {
                    float distance = Vector3.Distance(neighNode.position, current.position);
                    distance = currentNode.getgCost() + distance;

                    if (distance < node.getgCost())
                    {
                        node.setgCost(distance);
                        node.setParentNode(current);
                        node.transform.GetComponent<SpriteRenderer>().material.color = Color.gray;
                    }
                }
            }
        }
        return end;
    }

    private Transform aStar(Transform start, Transform end,int weight)
    {
        List<Transform> unexplored = new List<Transform>();

        foreach (GameObject obj in nodes)
        {
            Node n = obj.GetComponent<Node>();
            if (n.isWalkable())
            {
                n.resetNode();
                unexplored.Add(obj.transform);
            }
        }

        Node startNode = start.GetComponent<Node>();
        startNode.setgCost(0);
        startNode.setfCost(startNode.getgCost()+startNode.getHeuristic());

        while (unexplored.Count > 0)
        {
            // Sort the explored by their weight in ascending order.
            unexplored.Sort((x, y) => x.GetComponent<Node>().getfCost().CompareTo(y.GetComponent<Node>().getfCost()));

            Transform current = unexplored[0];

            if (current == end)
            {
                return end;
            }

            unexplored.Remove(current);

            Node currentNode = current.GetComponent<Node>();
            List<Transform> neighbours = currentNode.getNeighbourNode();
            foreach (Transform neighNode in neighbours)
            {
                Node node = neighNode.GetComponent<Node>();

                if (unexplored.Contains(neighNode) && node.isWalkable())
                {
                    float distance = Vector3.Distance(neighNode.position, current.position);
                    node.setHeuristic(Vector2.Distance(neighNode.position, end.position)* weight);
                    distance = currentNode.getgCost() + distance;
                    
                    if (distance < node.getgCost())
                    {
                        node.setgCost(distance);
                        node.setfCost(node.getHeuristic() + node.getgCost());
                        node.setParentNode(current);
                        node.transform.GetComponent<SpriteRenderer>().material.color = Color.gray;
                    }
                }
            }
        }
        return end;
    }
}
