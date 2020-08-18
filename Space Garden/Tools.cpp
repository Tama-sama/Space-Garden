#include "Tools.hpp"

Times MainTime;
sf::Font Font;

CAnimations::CAnimations(int AnimationLine, sf::Vector2i FrameSize, float _AnimationTiming, int _MaxFrames)
{
	m_AnimatedRect = sf::IntRect(0, AnimationLine * FrameSize.y, FrameSize.x, FrameSize.y);
	m_Size = FrameSize;
	m_line = AnimationLine;
	m_AnimationTime = _AnimationTiming;
	m_TotalFramesX = _MaxFrames;
	m_AnimationFrameX = 0;
	m_Timer = 0;
}

void CAnimations::Initialitation(int AnimationLine, sf::Vector2i FrameSize, float _AnimationTiming, int _MaxFrames)
{
	m_AnimatedRect = sf::IntRect(0, AnimationLine * FrameSize.y, FrameSize.x, FrameSize.y);
	m_Size = FrameSize;
	m_line = AnimationLine;
	m_AnimationTime = _AnimationTiming;
	m_TotalFramesX = _MaxFrames;
	m_AnimationFrameX = 0;
	m_Timer = 0;
}

void CAnimations::Animate(sf::Sprite& _SpriteSheet, int _Line)
{
	m_Timer += MainTime.GetTimeDeltaF();

	if (m_Timer > m_AnimationTime)
	{
		m_Timer = 0;

		if (_Line > -1)
			m_line = _Line;

		if (m_AnimationFrameX < m_TotalFramesX - 1)
			m_AnimationFrameX++;
		else
			m_AnimationFrameX = 1;

		m_AnimatedRect.top = m_line * m_Size.y;
		m_AnimatedRect.left = m_AnimationFrameX * m_Size.x;
	}

	_SpriteSheet.setTextureRect(m_AnimatedRect);
}



int random(int Min, int Max)
{
	return rand() % (Max - Min) + Min;
}

double random(float Min, float Max)
{
	return ((rand() / (double)RAND_MAX) * ((double)Max - (double)Min) + (double)Min);
}

bool Circle_Rect_Collision(sf::Vector2f CirclePosition, sf::Vector2f RectanglePosition, float CircleRadius, sf::Vector2f RectangleSize)
{
	sf::Vector2f Test(CirclePosition);

	if (CirclePosition.x < RectanglePosition.x)
		Test.x = RectanglePosition.x;
	else if (CirclePosition.x > RectanglePosition.x + RectangleSize.x)
		Test.x = RectanglePosition.x + RectangleSize.x;

	if (CirclePosition.y < RectanglePosition.y)
		Test.y = RectanglePosition.y;
	else if (CirclePosition.y > RectanglePosition.y + RectangleSize.y)
		Test.y = RectanglePosition.y + RectangleSize.y;

	sf::Vector2f Dist(CirclePosition.x - Test.x, CirclePosition.y - Test.y);
	float distance = sqrt((Dist.x * Dist.x) + (Dist.y * Dist.y));

	if (distance <= CircleRadius)
		return true;
	else
		return false;
}


bool Circle_Collision(sf::Vector2f Pos1, sf::Vector2f Pos2, float Rayon1, float Rayon2)
{
	if (sqrt(pow(Pos1.x - Pos2.x, 2) + pow(Pos1.y - Pos2.y, 2)) < Rayon1 + Rayon2)
	{
		return true;
	}
	else return false;
}

float Angle_calc(sf::Vector2f pointA, sf::Vector2f pointB)
{
	float angle;
	if (pointA.y < pointB.y)
		angle = (float)acos(((double)pointB.x - pointA.x) / (sqrt(pow((double)pointB.x - pointA.x, 2) + pow((double)pointB.y - pointA.y, 2))));
	else
		angle = (float)-acos(((double)pointB.x - pointA.x) / (sqrt(pow((double)pointB.x - pointA.x, 2) + pow((double)pointB.y - pointA.y, 2))));

	return angle;
}










void LaunchArguments(int argc, char** argv)
{
	int i = 0;

	while (argv[++i])
	{
		std::cout << argv[i] << std::endl;
	}
}

void ProgramEnd()
{

}