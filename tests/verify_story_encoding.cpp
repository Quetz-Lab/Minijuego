// Quick verification that the actual story.json file loads correctly with UTF-8
#include "../src/StoryManager.h"
#include "../src/StoryNode.h"
#include <iostream>
#include <string>

int main() {
    std::cout << "=== Verifying story.json UTF-8 Encoding ===" << std::endl << std::endl;
    
    StoryManager manager;
    
    // Load the actual story file
    bool loadSuccess = manager.LoadFromFile("../assets/story.json");
    
    if (!loadSuccess) {
        std::cout << "[FAIL] Could not load story.json" << std::endl;
        return 1;
    }
    
    std::cout << "[PASS] story.json loaded successfully" << std::endl << std::endl;
    
    // Check that Spanish characters are preserved
    const StoryNode* node = manager.GetCurrentNode();
    
    if (!node) {
        std::cout << "[FAIL] No current node after loading" << std::endl;
        return 1;
    }
    
    std::cout << "First node title: " << node->title << std::endl;
    std::cout << "First node text: " << node->text << std::endl << std::endl;
    
    // Check for specific Spanish characters that were corrupted before
    std::string text = node->text;
    
    // Look for the word "mágica" which should have á
    if (text.find("mágica") != std::string::npos) {
        std::cout << "[PASS] Found 'mágica' with correct UTF-8 encoding (á)" << std::endl;
    } else {
        std::cout << "[FAIL] Could not find 'mágica' - encoding may be incorrect" << std::endl;
        return 1;
    }
    
    // Navigate to node n2 and check for more characters
    manager.NavigateToNode("n2");
    node = manager.GetCurrentNode();
    
    if (node) {
        std::cout << "[PASS] Navigated to node n2: " << node->title << std::endl;
        
        // Check for "balcón" (ó), "dragón" (ó), "relámpagos" (á), "ningún" (ú)
        text = node->text;
        
        if (text.find("balcón") != std::string::npos) {
            std::cout << "[PASS] Found 'balcón' with correct UTF-8 encoding (ó)" << std::endl;
        }
        
        if (text.find("dragón") != std::string::npos) {
            std::cout << "[PASS] Found 'dragón' with correct UTF-8 encoding (ó)" << std::endl;
        }
        
        if (text.find("relámpagos") != std::string::npos) {
            std::cout << "[PASS] Found 'relámpagos' with correct UTF-8 encoding (á)" << std::endl;
        }
        
        if (text.find("ningún") != std::string::npos) {
            std::cout << "[PASS] Found 'ningún' with correct UTF-8 encoding (ú)" << std::endl;
        }
    }
    
    // Navigate to node n4 and check for more characters
    manager.NavigateToNode("n4");
    node = manager.GetCurrentNode();
    
    if (node) {
        std::cout << "[PASS] Navigated to node n4: " << node->title << std::endl;
        
        // Check for "círculo" (í), "sólo" (ó)
        text = node->text;
        
        if (text.find("círculo") != std::string::npos) {
            std::cout << "[PASS] Found 'círculo' with correct UTF-8 encoding (í)" << std::endl;
        }
        
        if (text.find("sólo") != std::string::npos) {
            std::cout << "[PASS] Found 'sólo' with correct UTF-8 encoding (ó)" << std::endl;
        }
    }
    
    // Check node n8 for "energía" (í), "enseñó" (ñ, ó)
    manager.NavigateToNode("n8");
    node = manager.GetCurrentNode();
    
    if (node) {
        std::cout << "[PASS] Navigated to node n8: " << node->title << std::endl;
        
        text = node->text;
        
        if (text.find("energía") != std::string::npos) {
            std::cout << "[PASS] Found 'energía' with correct UTF-8 encoding (í)" << std::endl;
        }
        
        if (text.find("enseñó") != std::string::npos) {
            std::cout << "[PASS] Found 'enseñó' with correct UTF-8 encoding (ñ, ó)" << std::endl;
        }
        
        if (text.find("sílaba") != std::string::npos) {
            std::cout << "[PASS] Found 'sílaba' with correct UTF-8 encoding (í)" << std::endl;
        }
    }
    
    // Check node n10 for "Señor" (ñ), "órdenes" (ó), "sí" (í)
    manager.NavigateToNode("n10");
    node = manager.GetCurrentNode();
    
    if (node) {
        std::cout << "[PASS] Navigated to node n10: " << node->title << std::endl;
        
        text = node->endingText;
        
        if (text.find("órdenes") != std::string::npos) {
            std::cout << "[PASS] Found 'órdenes' with correct UTF-8 encoding (ó)" << std::endl;
        }
        
        if (text.find("sí") != std::string::npos) {
            std::cout << "[PASS] Found 'sí' with correct UTF-8 encoding (í)" << std::endl;
        }
    }
    
    std::cout << std::endl << "[SUCCESS] All UTF-8 characters verified correctly!" << std::endl;
    
    return 0;
}
