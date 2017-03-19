#include "World.h"

#include <iostream>
#include <SFML/Graphics.hpp>

#include "../Renderer/RMaster.h"

#include "../Player/Player.h"

World::World(const Camera& camera, int32_t worldSize)
:   m_p_camera      (&camera)
,   m_worldSize     (worldSize)
{
    for (int32_t x = 0 ; x < m_worldSize; x++)
    {
        for (int32_t z = 0; z < m_worldSize; z++)
        {
                m_chunks.m_chunks.insert(std::make_pair(Chunk::Position(x, z),
                                                        std::make_unique<Chunk::Section>(Chunk::Chunklet_Position(x, 0, z), m_chunks
                                                                                         )));
        }
    }

}

void World::checkPlayerBounds(Player& player)
{
    if (player.position.x < 0.2)
    {
        player.position.x = 0.2;
    }
    if (player.position.z < 0.2)
    {
        player.position.z = 0.2;
    }

    if (player.position.x + 0.2 > m_worldSize * CHUNK_SIZE - 0.2 )
    {
        player.position.x = m_worldSize * CHUNK_SIZE - 0.2;
    }
    if (player.position.z + 0.2 > m_worldSize * CHUNK_SIZE - 0.2 )
    {
        player.position.z = m_worldSize * CHUNK_SIZE - 0.2;
    }
}

void World::drawWorld(Renderer::Master& renderer)
{
    bool isMeshMade = false;
    for (int32_t x = 0 ; x < m_worldSize; x++)
    {
        for (int32_t z = 0; z < m_worldSize; z++)
        {
            if (!m_chunks.get({x, z})->made)
            {
                m_chunks.get({x, z})->makeMesh();
                isMeshMade = true;
                break;
            }
            else
            {
                renderer.draw(*m_chunks.get({x, z}));
            }
        }
        if (isMeshMade)
        {
            break;
        }
    }
}
