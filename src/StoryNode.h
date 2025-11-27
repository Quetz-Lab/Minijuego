#pragma once

#include <string>
#include <vector>

/**
 * @struct StoryOption
 * @brief Represents a player choice/option in the story
 * 
 * Each option has an ID (e.g., "A", "B"), display text, and the ID
 * of the next node to navigate to when selected.
 */
struct StoryOption {
    std::string id;           // "A", "B", etc.
    std::string text;         // Text displayed for the option
    std::string nextNodeId;   // ID of the node to navigate to
};

/**
 * @class StoryNode
 * @brief Represents a single node/scene in the interactive story
 * 
 * Contains all data for a story scene including title, narrative text,
 * player options, and ending information. Nodes form a directed graph
 * where options link to other nodes.
 */
class StoryNode {
public:
    std::string id;
    std::string title;
    std::string text;
    std::vector<StoryOption> options;
    bool isEnding;
    std::string outcome;      // "final_bueno", "final_malo", etc.
    std::string endingText;   // Extended ending description
    
    StoryNode();
    
    // Check if this node has any options
    bool HasOptions() const;
    
    // Get a specific option by its id (returns nullptr if not found)
    const StoryOption* GetOption(const std::string& optionId) const;
};
