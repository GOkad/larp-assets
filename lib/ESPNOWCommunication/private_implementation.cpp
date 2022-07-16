
#include <memory>

struct esp_context;

class esp_p
{
    using context_t = std::unique_ptr<esp_context>;

public:
    esp_p();
    ~esp_p();

public:
    bool initialize();

private:
    static void zero_context(eps_context* context);
    static void zero_context(const context_t& context);

private:
    context_t m_context;
}

// .cpp = 32 / 82

struct esp_context
{
    // esp32_context
    // esp82_context
};

esp_p::esp_p()
{
    m_context = std::make_unique<esp_context>();
}

esp_p::~esp_p() = default;

bool esp_p::initialize()
{
    return false;
}

