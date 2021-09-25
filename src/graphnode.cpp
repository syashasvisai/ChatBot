#include "graphedge.h"
#include "graphnode.h"

GraphNode::GraphNode(int id)
{
    _id = id;
}

GraphNode::~GraphNode(){}

void GraphNode::AddToken(std::string token)
{
    _answers.push_back(token);
}

void GraphNode::AddEdgeToParentNode(GraphEdge *edge)
{
    _parentEdges.push_back(edge);
}

void GraphNode::AddEdgeToChildNode(std::unique_ptr<GraphEdge> edge)
{
  // Answer from forum : push_back() creates a copy of the element you are adding to it, and hence you get the error that you are trying to use copy assignment on a `unique_ptr`, which is not allowed. Hence, you need to transfer ownership from the pointer passed into the function to the `unique_ptr` in the `vector` container.
  
    _childEdges.push_back(std::move(edge));
}

void GraphNode::MoveChatbotHere(ChatBot chatbot)
{
  _chatBot = std::move(chatbot);
  _chatBot.SetCurrentNode(this);
}

void GraphNode::MoveChatbotToNewNode(GraphNode *newNode)
{
  newNode->MoveChatbotHere(std::move(_chatBot));
}


GraphEdge *GraphNode::GetChildEdgeAtIndex(int index)
{
  // _childEdges is a smart pointer, use get()
    return _childEdges[index].get();
}