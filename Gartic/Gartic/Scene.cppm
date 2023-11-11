export module Scene;

import <typeindex>;

export class Scene
{
public:
    std::type_info* SetActive();
    virtual ~Scene();

protected:
	std::type_info* m_nextScene;

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Display() const = 0;
};