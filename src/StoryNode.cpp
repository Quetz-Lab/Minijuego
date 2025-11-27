#include "StoryNode.h"

StoryNode::StoryNode()
    : isEnding(false)
{
}

bool StoryNode::HasOptions() const
{
    return !options.empty();
}

const StoryOption* StoryNode::GetOption(const std::string& optionId) const
{
    for (const auto& option : options)
    {
        if (option.id == optionId)
        {
            return &option;
        }
    }
    return nullptr;
}
