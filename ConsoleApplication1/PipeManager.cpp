#include "PipeManager.h"
#include "Pipe_Object.h"
#include <time.h>
#include "Bird_Object.h"

PipeManager::PipeManager()
	:m_pipesCount(0)
	, m_lastRnd(0.0)
{
	time(NULL);
}

PipeManager::~PipeManager()
{
	for (auto pipe : m_pipes)
	{
		delete pipe;
	}
	m_pipes.clear();
}

void PipeManager::AddPipe(bool isTop)
{
	if (isTop)
	{
		m_lastRnd = (std::rand() % 5) / 10.0;
		for (int i = 0; i < 4; i++)
		{
			initial_top_position[i].m_pos.x += 0.8;
			if (i == 0 || i == 3)
			{
				initial_top_position[i].m_pos.y = 0.2 + m_lastRnd;
			}
		}
		PipeObject* top_pipe = new PipeObject();
		top_pipe->Init("tubeShader.vs", "tubeShader.fs", initial_top_position, "top_tube.tga", PipeObject::TYPE::TOP);
		m_pipes.push_back(top_pipe);
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			initial_bot_position[i].m_pos.x += 0.8;
			if (i == 1 || i == 2)
			{
				initial_bot_position[i].m_pos.y = -0.6 + m_lastRnd;
			}
		}
		PipeObject* bot_pipe = new PipeObject();
		bot_pipe->Init("tubeShader.vs", "tubeShader.fs", initial_bot_position, "bot_tube.tga", PipeObject::TYPE::BOTTOM);
		m_pipes.push_back(bot_pipe);
		m_lastRnd = 0.0;
	}

	m_pipesCount++;
}

void PipeManager::DrawPipes(double dt)
{
	for (auto const & pipe : m_pipes)
	{
		pipe->Draw(dt);
	}
}

void PipeManager::DeletePipes()
{
	for (int i = 0; i < m_pipes.size(); i++)
	{
		if (m_pipes[i]->ShouldBeDeleted())
		{
			AddPipe(m_pipes[i]->GetType() == PipeObject::TYPE::TOP);
			delete m_pipes[i];
			m_pipes.erase(m_pipes.begin() + i);
		}
	}
}

bool PipeManager::CheckCollisionWithBird(BirdObject& bird)
{
	for (auto const & pipe : m_pipes)
	{
		if (bird.CheckInteractWithTube(pipe))
			return true;
	}
	return false;
}

bool PipeManager::CheckScore(BirdObject& bird)
{
	for (auto const & pipe : m_pipes)
	{
		if (!pipe->IsScored() && pipe->GetType() == PipeObject::TYPE::TOP)
		{
			if (bird.ChechScore(pipe))
			{
				pipe->SetIsScored(true);
				return true;
			}
		}
	}
	return false;
}

std::vector<PipeObject*> PipeManager::GetPipes() const
{
	return m_pipes;
}