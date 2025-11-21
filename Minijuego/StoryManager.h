#pragma once

#include <string>
#include <vector>
#include <unordered_map>

struct StoryOption
{
    std::string id;
    std::string text;
    std::string nextNodeId;
};

struct StoryNode
{
    std::string id;
    std::string title;
    std::string text;
    std::vector<StoryOption> options;

    bool        isEnding = false;
    std::string outcome;
    std::string textEnding;
};

class StoryManager
{
public:
    bool LoadFromFile(const std::string& path);

    const StoryNode* GetCurrentNode() const;
    bool GoToNode(const std::string& id);

private:
    std::unordered_map<std::string, StoryNode> m_nodes;
    std::string m_currentNodeId;
};
