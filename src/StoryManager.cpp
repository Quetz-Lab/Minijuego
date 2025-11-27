#include "StoryManager.h"
#include "json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

StoryManager::StoryManager()
    : m_startNodeId("")
    , m_currentNodeId("")
{
}

StoryManager::~StoryManager()
{
    // m_nodes (unordered_map) automatically cleans up all StoryNode objects
    // No manual cleanup needed as we don't use raw pointers
}

bool StoryManager::LoadFromFile(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        std::cerr << "Error: No se pudo abrir el archivo de historia: " << path << std::endl;
        return false;
    }

    json j;
    try
    {
        file >> j;
    }
    catch (const json::parse_error& e)
    {
        std::cerr << "Error: JSON invalido - " << e.what() << std::endl;
        return false;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error al parsear JSON: " << e.what() << std::endl;
        return false;
    }

    try
    {
        ParseJSON(j);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error al procesar datos de historia: " << e.what() << std::endl;
        return false;
    }

    return true;
}

void StoryManager::ParseJSON(const nlohmann::json& jsonData)
{
    m_nodes.clear();

    // Validate that JSON contains required top-level fields
    if (!jsonData.contains("nodes") || !jsonData["nodes"].is_array())
    {
        throw std::runtime_error("El JSON no contiene 'nodes' o no es un array");
    }

    if (!jsonData.contains("startNodeId") || !jsonData["startNodeId"].is_string())
    {
        throw std::runtime_error("El JSON no contiene 'startNodeId' o no es una cadena");
    }

    // Parse all story nodes from the JSON array
    for (const auto& nodeJson : jsonData["nodes"])
    {
        StoryNode node = ParseNode(nodeJson);
        
        // Only add nodes with valid IDs to the map
        if (!node.id.empty())
        {
            m_nodes[node.id] = node;
        }
    }

    // Store and validate the starting node ID
    m_startNodeId = jsonData["startNodeId"].get<std::string>();
    
    if (m_startNodeId.empty())
    {
        throw std::runtime_error("El 'startNodeId' esta vacio");
    }

    // Verify that the start node actually exists in the loaded nodes
    if (m_nodes.find(m_startNodeId) == m_nodes.end())
    {
        throw std::runtime_error("El 'startNodeId' no corresponde a ningun nodo cargado");
    }

    // Initialize current position to the start of the story
    m_currentNodeId = m_startNodeId;
}

StoryNode StoryManager::ParseNode(const nlohmann::json& nodeJson)
{
    StoryNode node;

    // Validate that the node has a required ID field
    if (!nodeJson.contains("id") || !nodeJson["id"].is_string())
    {
        throw std::runtime_error("Nodo sin campo 'id' valido");
    }

    // Parse basic node properties (using value() for optional fields with defaults)
    node.id = nodeJson["id"].get<std::string>();
    node.title = nodeJson.value("title", "");
    node.text = nodeJson.value("text", "");

    // Parse player choice options if present
    if (nodeJson.contains("options") && nodeJson["options"].is_array())
    {
        for (const auto& optJson : nodeJson["options"])
        {
            StoryOption opt;
            opt.id = optJson.value("id", "");
            opt.text = optJson.value("text", "");
            opt.nextNodeId = optJson.value("nextNodeId", "");
            
            // Skip invalid options (missing required fields)
            if (opt.id.empty() || opt.nextNodeId.empty())
            {
                std::cerr << "Advertencia: Opcion invalida en nodo " << node.id << std::endl;
                continue;
            }
            
            node.options.push_back(opt);
        }
    }

    // Parse ending-related fields (for terminal story nodes)
    node.isEnding = nodeJson.value("ending", false);
    node.outcome = nodeJson.value("outcome", "");
    node.endingText = nodeJson.value("textEnding", "");

    return node;
}

void StoryManager::Start()
{
    if (m_startNodeId.empty())
    {
        std::cerr << "Error: No se ha cargado ninguna historia" << std::endl;
        return;
    }
    
    m_currentNodeId = m_startNodeId;
}

bool StoryManager::NavigateToNode(const std::string& nodeId)
{
    auto it = m_nodes.find(nodeId);
    if (it == m_nodes.end())
    {
        std::cerr << "Error: Nodo no encontrado: " << nodeId << std::endl;
        return false;
    }

    // Check if current node is an ending
    const StoryNode* currentNode = GetCurrentNode();
    if (currentNode && currentNode->isEnding)
    {
        std::cerr << "Advertencia: Intentando navegar desde un nodo final" << std::endl;
        return false;
    }

    m_currentNodeId = nodeId;
    return true;
}

bool StoryManager::SelectOption(const std::string& optionId)
{
    const StoryNode* currentNode = GetCurrentNode();
    if (!currentNode)
    {
        std::cerr << "Error: No hay nodo actual" << std::endl;
        return false;
    }

    // Check if at ending
    if (currentNode->isEnding)
    {
        std::cerr << "Error: No se puede seleccionar opciones en un nodo final" << std::endl;
        return false;
    }

    // Find the option
    const StoryOption* option = currentNode->GetOption(optionId);
    if (!option)
    {
        std::cerr << "Error: Opcion no encontrada: " << optionId << std::endl;
        return false;
    }

    // Navigate to the next node
    return NavigateToNode(option->nextNodeId);
}

const StoryNode* StoryManager::GetCurrentNode() const
{
    if (m_currentNodeId.empty())
    {
        return nullptr;
    }
    
    auto it = m_nodes.find(m_currentNodeId);
    if (it == m_nodes.end())
    {
        return nullptr;
    }
    
    return &it->second;
}

bool StoryManager::IsAtEnding() const
{
    const StoryNode* currentNode = GetCurrentNode();
    return currentNode && currentNode->isEnding;
}

bool StoryManager::GoToNode(const std::string& id)
{
    return NavigateToNode(id);
}
