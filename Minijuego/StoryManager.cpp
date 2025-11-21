#include "StoryManager.h"
#include "json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

bool StoryManager::LoadFromFile(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        std::cerr << "No se pudo abrir el archivo de historia: " << path << std::endl;
        return false;
    }

    json j;
    try
    {
        file >> j;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error al parsear JSON: " << e.what() << std::endl;
        return false;
    }

    m_nodes.clear();

    if (!j.contains("nodes") || !j["nodes"].is_array())
    {
        std::cerr << "El JSON no contiene 'nodes' o no es un array.\n";
        return false;
    }

    for (const auto& nodeJson : j["nodes"])
    {
        StoryNode node;

        node.id = nodeJson.value("id", "");
        node.title = nodeJson.value("title", "");
        node.text = nodeJson.value("text", "");

        if (nodeJson.contains("options") && nodeJson["options"].is_array())
        {
            for (const auto& optJson : nodeJson["options"])
            {
                StoryOption opt;
                opt.id = optJson.value("id", "");
                opt.text = optJson.value("text", "");
                opt.nextNodeId = optJson.value("nextNodeId", "");
                node.options.push_back(opt);
            }
        }

        node.isEnding = nodeJson.value("ending", false);
        node.outcome = nodeJson.value("outcome", "");
        node.textEnding = nodeJson.value("textEnding", "");

        if (!node.id.empty())
        {
            m_nodes[node.id] = node;
        }
    }

    m_currentNodeId = j.value("startNodeId", "");
    if (m_currentNodeId.empty())
    {
        std::cerr << "El JSON no define 'startNodeId'.\n";
        return false;
    }

    if (m_nodes.find(m_currentNodeId) == m_nodes.end())
    {
        std::cerr << "El 'startNodeId' no corresponde a ningún nodo cargado.\n";
        return false;
    }

    return true;
}

const StoryNode* StoryManager::GetCurrentNode() const
{
    auto it = m_nodes.find(m_currentNodeId);
    if (it == m_nodes.end()) return nullptr;
    return &it->second;
}

bool StoryManager::GoToNode(const std::string& id)
{
    auto it = m_nodes.find(id);
    if (it == m_nodes.end())
    {
        return false;
    }

    m_currentNodeId = id;
    return true;
}
