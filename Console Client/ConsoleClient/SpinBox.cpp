module SpinBox;

SpinBox::SpinBox(COORD upLeftCorner, Align horizontalAlign, Align verticalAlign,
				 ColorType backgroundColor, ColorType textColor,
				 int16_t maxWidth, int16_t maxHeight,
				 ConsoleManager* cm, InputManager* im, SelectableObject*& selected,
				 ColorType buttonsBackgroundColor, ColorType buttonsTextColor,
				 ColorType buttonsSelectedBackgroungColor, ColorType buttonsSelectedTextColor) :
	SelectableObject { upLeftCorner, horizontalAlign, verticalAlign, backgroundColor, textColor,
					   maxWidth, maxHeight, backgroundColor, textColor, cm, im, selected }
{
	m_left = new Button{ m_upLeftCorner, Align::Center, Align::Center,
			buttonsBackgroundColor, buttonsTextColor, 1, m_height,
			buttonsSelectedBackgroungColor, buttonsSelectedTextColor,
			cm, im, selected, "<" };
	m_left->SetFunctionOnActivate(std::bind(&SpinBox::PreviousOption, this));

	m_right = new Button{ static_cast<int16_t>(m_upLeftCorner.X + maxWidth - 1),
			m_upLeftCorner.Y, Align::Center, Align::Center, buttonsBackgroundColor,
			buttonsTextColor, 1, m_height, buttonsSelectedBackgroungColor,
			buttonsSelectedTextColor, cm, im, selected, ">" };
	m_right->SetFunctionOnActivate(std::bind(&SpinBox::NextOption, this));

	m_left->SetConections(nullptr, nullptr, nullptr, m_right);
	m_right->SetConections(nullptr, nullptr, m_left, nullptr);
}

SpinBox::SpinBox(int16_t x, int16_t y, Align horizontalAlign, Align verticalAlign,
				 ColorType backgroundColor, ColorType textColor,
				 int16_t maxWidth, int16_t maxHeight,
				 ConsoleManager* cm, InputManager* im, SelectableObject*& selected,
				 ColorType buttonsBackgroundColor, ColorType buttonsTextColor,
				 ColorType buttonsSelectedBackgroungColor, ColorType buttonsSelectedTextColor) :
	SelectableObject { x, y, horizontalAlign, verticalAlign, backgroundColor, textColor,
					   maxWidth, maxHeight, backgroundColor, textColor, cm, im, selected }
{
	m_left = new Button{ m_upLeftCorner, Align::Center, Align::Center,
			buttonsBackgroundColor, buttonsTextColor, 1, m_height,
			buttonsSelectedBackgroungColor, buttonsSelectedTextColor,
			cm, im, selected, "<" };
	m_left->SetFunctionOnActivate(std::bind(&SpinBox::PreviousOption, this));

	m_right = new Button{ static_cast<int16_t>(m_upLeftCorner.X + maxWidth - 1),
			m_upLeftCorner.Y, Align::Center, Align::Center, buttonsBackgroundColor,
			buttonsTextColor, 1, m_height, buttonsSelectedBackgroungColor,
			buttonsSelectedTextColor, cm, im, selected, ">" };
	m_right->SetFunctionOnActivate(std::bind(&SpinBox::NextOption, this));

	m_left->SetConections(nullptr, nullptr, nullptr, m_right);
	m_right->SetConections(nullptr, nullptr, m_left, nullptr);
}

SpinBox::SpinBox(Align horizontalAlign, Align verticalAlign,
				 ColorType backgroundColor, ColorType textColor,
				 int16_t maxWidth, int16_t maxHeight,
				 ConsoleManager* cm, InputManager* im, SelectableObject*& selected,
				 ColorType buttonsBackgroundColor, ColorType buttonsTextColor,
				 ColorType buttonsSelectedBackgroungColor, ColorType buttonsSelectedTextColor) :
	SelectableObject { horizontalAlign, verticalAlign, backgroundColor, textColor,
					   maxWidth, maxHeight, backgroundColor, textColor, cm, im, selected }
{
	m_left = new Button{ m_upLeftCorner, Align::Center, Align::Center,
			buttonsBackgroundColor, buttonsTextColor, 1, m_height,
			buttonsSelectedBackgroungColor, buttonsSelectedTextColor,
			cm, im, selected, "<" };
	m_left->SetFunctionOnActivate(std::bind(&SpinBox::PreviousOption, this));

	m_right = new Button{ static_cast<int16_t>(m_upLeftCorner.X + maxWidth - 1),
			m_upLeftCorner.Y, Align::Center, Align::Center, buttonsBackgroundColor,
			buttonsTextColor, 1, m_height, buttonsSelectedBackgroungColor,
			buttonsSelectedTextColor, cm, im, selected, ">" };
	m_right->SetFunctionOnActivate(std::bind(&SpinBox::NextOption, this));

	m_left->SetConections(nullptr, nullptr, nullptr, m_right);
	m_right->SetConections(nullptr, nullptr, m_left, nullptr);
}

SpinBox::~SpinBox()
{
	delete m_right;
	delete m_left;
}

void SpinBox::SetOptions(Options options, int startOption)
{
	m_options = options;
	m_optionSelected = startOption;
}

void SpinBox::SetOption(String option)
{
	auto it{ std::find(m_options.begin(), m_options.end(), option) };
	if (it != m_options.end())
		m_optionSelected = it - m_options.begin();
}

void SpinBox::SetHoverColors(ColorType backgroundColor, ColorType textColor)
{
	m_left->SetHoverColors(backgroundColor, textColor);
	m_right->SetHoverColors(backgroundColor, textColor);
}

void SpinBox::SetConections(SelectableObject* up, SelectableObject* down,
							SelectableObject* left, SelectableObject* right)
{
	m_left->SetConections(up, down, nullptr, m_right);
	m_right->SetConections(up, down, m_left, nullptr);
}

void SpinBox::SetFunctionOnActivate(Function function, std::string argument)
{
	auto leftFunctionWrapper{ [function, this](std::string argument)
		{
			PreviousOption();
			function(argument);
		} };
	auto rightFunctionWrapper{ [function, this](std::string argument)
		{
			NextOption();
			function(argument);
		} };
	m_left->SetFunctionOnActivate(leftFunctionWrapper);
	m_right->SetFunctionOnActivate(rightFunctionWrapper);
}

void SpinBox::Draw()
{
	SetColor();

	DrawBackground();

	DrawContents();
}

void SpinBox::InitializeTransform(COORD upLeftCorner)
{
	m_upLeftCorner = upLeftCorner;
	m_left->InitializeTransform(m_upLeftCorner);
	m_right->InitializeTransform({ static_cast<int16_t>(m_upLeftCorner.X + m_width - 1), m_upLeftCorner.Y });
}

void SpinBox::CheckCursor()
{
	if (!m_selectable) return;
	m_left->CheckCursor();
	m_right->CheckCursor();
}

void SpinBox::CheckInput()
{
	if (this == m_selectedObject)
	{
		m_selectedObject = m_left;
		m_left->CheckInput();
	}
}

String SpinBox::GetOption() const
{
	return m_options[m_optionSelected];
}

void SpinBox::DrawContents()
{
	m_left->Draw();
	m_right->Draw();

	SetColor();

	m_cm->Write(m_options[m_optionSelected], m_upLeftCorner.X + 1, m_upLeftCorner.Y,
				m_width - 2, m_height, m_horizontalAlign, m_verticalAlign);
}

void SpinBox::PreviousOption()
{
	if (m_optionSelected > 0)
		--m_optionSelected;
	if (m_optionSelected == 0)
		m_left->CanBeSelected(false);
	m_right->CanBeSelected(true);
}

void SpinBox::NextOption()
{
	if (m_optionSelected < m_options.size() - 1)
		++m_optionSelected;
	if (m_optionSelected == m_options.size() - 1)
		m_right->CanBeSelected(false);
	m_left->CanBeSelected(true);
}
