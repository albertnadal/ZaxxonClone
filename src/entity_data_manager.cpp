#include <entity_data_manager.h>
#include <fstream>
#include <sstream>
#include <collision/collision.h>

using namespace collision;

EntityDataManager::EntityDataManager()
{
        LoadObjectsDataFromFile(ENTITIES_DATA_FILENAME);
}

EntityDataManager::~EntityDataManager() {
        for (auto& kv : entitySpriteSheetsMap) {
                EntitySpriteSheet* entitySpriteSheet = kv.second;
                delete entitySpriteSheet;
        }

        entitySpriteSheetsMap.clear();
}

void EntityDataManager::LoadObjectsDataFromFile(std::string filename)
{
        enum LineType { UNDEFINED_LINE_TYPE, OBJ_TEX_FILENAME, OBJ_ID, OBJ_ANIMATION_ID, OBJ_SPRITE };

        std::ifstream infile(filename);
        std::string line;
        EntitySpriteSheet *currentEntitySpriteSheet;
        EntitySpriteSheetAnimation *currentEntitySpriteSheetAnimation;

        while (std::getline(infile, line))
        {
                std::istringstream iss(line);
                string token;
                bool commentFound = false;
                std::vector<string> currentFrameValues;
                LineType currentLineType = UNDEFINED_LINE_TYPE;

                while((iss >> token) && (!commentFound)) {
                        if(startsWith(token, "//")) {
                                commentFound = true;
                        } else if(startsWith(token, "###")) {
                                currentLineType = OBJ_TEX_FILENAME;
                                textureFilename = token.substr(3);
                        } else if(startsWith(token, "##")) {
                                currentLineType = OBJ_ID;
                                EntityIdentificator entityId = (EntityIdentificator)std::stoi(token.substr(2));
                                currentEntitySpriteSheet = new EntitySpriteSheet();
                                entitySpriteSheetsMap[entityId] = currentEntitySpriteSheet;
                        } else if(startsWith(token, "#")) {
                                currentLineType = OBJ_ANIMATION_ID;
                                uint16_t entitySpriteSheetAnimationId = std::stoi(token.substr(1));
                                currentEntitySpriteSheetAnimation = new EntitySpriteSheetAnimation(entitySpriteSheetAnimationId);
                                currentEntitySpriteSheet->AddAnimation(currentEntitySpriteSheetAnimation);
                        } else {
                                currentLineType = OBJ_SPRITE;
                                currentFrameValues.push_back(token);
                        }
                }

                if(currentLineType == OBJ_SPRITE) {
                        if(currentFrameValues.size() >= 15) {
                                int width = stoi(currentFrameValues.at(0));
                                int height = stoi(currentFrameValues.at(1));
                                int xOffset = stoi(currentFrameValues.at(2));
                                int yOffset = stoi(currentFrameValues.at(3));
                                float u1 = stof(currentFrameValues.at(4));
                                float v1 = stof(currentFrameValues.at(5));
                                float u2 = stof(currentFrameValues.at(6));
                                float v2 = stof(currentFrameValues.at(7));
                                int duration = stoi(currentFrameValues.at(8));
                                int lowerBoundX = stoi(currentFrameValues.at(9));
                                int lowerBoundY = stoi(currentFrameValues.at(10));
                                int lowerBoundZ = stoi(currentFrameValues.at(11));
                                int upperBoundX = stoi(currentFrameValues.at(12));
                                int upperBoundY = stoi(currentFrameValues.at(13));
                                int upperBoundZ = stoi(currentFrameValues.at(14));
                                bool hasAttack = false;
                                int attackLowerBoundX = 0, attackLowerBoundY = 0, attackUpperBoundX = 0, attackUpperBoundY = 0;

                                if(currentFrameValues.size() == 19) {
                                        attackLowerBoundX = stoi(currentFrameValues.at(15));
                                        attackLowerBoundY = stoi(currentFrameValues.at(16));
                                        attackUpperBoundX = stoi(currentFrameValues.at(17));
                                        attackUpperBoundY = stoi(currentFrameValues.at(18));
                                        hasAttack = true;
                                }

                                // An sprite may contain areas defined by rectangles in order to check for basic and attack collisions with other objects during the gameplay
                                currentEntitySpriteSheetAnimation->AddSprite({ width, height, xOffset, yOffset, u1, v1, u2, v2, duration, false, lowerBoundX, lowerBoundY, lowerBoundZ, upperBoundX, upperBoundY, upperBoundZ, hasAttack, attackLowerBoundX, attackLowerBoundY, attackUpperBoundX, attackUpperBoundY });
                        }
                }
        }
}

Texture2D EntityDataManager::LoadTextureAtlas() const {
        Image img = LoadImage(FileSystem::getPath(textureFilename).c_str());
        ImageColorReplace(&img, CHROMA_KEY_COLOR, BLANK);
        Texture2D texture = LoadTextureFromImage(img);
        UnloadImage(img);
        return texture;
}

std::optional<EntitySpriteSheet*> EntityDataManager::GetSpriteSheetByEntityIdentificator(EntityIdentificator entityId) const {
        auto searchIterator = entitySpriteSheetsMap.find(entityId);
        if (searchIterator != entitySpriteSheetsMap.end()) {
                return searchIterator->second;
        }

        return std::nullopt;
}

bool startsWith(std::string mainStr, std::string toMatch)
{
        // Convert mainStr to lower case
        std::transform(mainStr.begin(), mainStr.end(), mainStr.begin(), ::tolower);
        // Convert toMatch to lower case
        std::transform(toMatch.begin(), toMatch.end(), toMatch.begin(), ::tolower);

        return (mainStr.find(toMatch) == 0);
}
