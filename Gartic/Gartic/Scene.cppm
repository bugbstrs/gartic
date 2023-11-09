export module Scene;

import <typeindex>;

export import SceneType;

export class Scene
{
public:
    SceneType SetActive();
    virtual ~Scene();
protected:
	SceneType m_nextScene;

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Display() = 0;
};