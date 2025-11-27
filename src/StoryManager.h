#pragma once

#include "StoryNode.h"
#include "json.hpp"
#include <string>
#include <unordered_map>

/**
 * @class StoryManager
 * @brief Manages story loading, parsing, and navigation
 * 
 * Handles loading story data from JSON files, parsing nodes and options,
 * and managing navigation through the story graph. Validates story structure
 * and ensures proper UTF-8 encoding for Spanish text.
 */
class StoryManager
{
public:
    StoryManager();
    ~StoryManager();
    
    // Load story from JSON file
    bool LoadFromFile(const std::string& path);
    
    // Navigate to the starting node
    void Start();
    
    // Navigate to a specific node by ID
    bool NavigateToNode(const std::string& nodeId);
    
    // Select an option from the current node
    bool SelectOption(const std::string& optionId);
    
    // Get the current node
    const StoryNode* GetCurrentNode() const;
    
    // Check if at an ending node
    bool IsAtEnding() const;
    
    // Legacy method for compatibility
    bool GoToNode(const std::string& id);

private:
    std::unordered_map<std::string, StoryNode> m_nodes;
    std::string m_startNodeId;
    std::string m_currentNodeId;
    
    void ParseJSON(const nlohmann::json& jsonData);
    StoryNode ParseNode(const nlohmann::json& nodeJson);
};
