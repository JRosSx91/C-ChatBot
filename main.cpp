#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <string>

std::string chatWithGpt3(std::string message, std::string model = "gpt-3.5-turbo")
{
    nlohmann::json requestBody = {
        {"model", model},
        {"messages", nlohmann::json::array({{{"role", "user"}, {"content", message}}})},
    };

    cpr::Response response = cpr::Post(
        cpr::Url{"https://api.openai.com/v1/chat/completions"},
        cpr::Header{{"Authorization", "Bearer " + std::getenv("OPENAI_KEY")}, {"Content-Type", "application/json"}},
        cpr::Body{requestBody.dump()});

    auto responseBody = nlohmann::json::parse(response.text);
    std::string gpt3Response = responseBody["choices"][0]["message"]["content"];
    return gpt3Response;
}

int main()
{
    std::string userMessage;
    while (true)
    {
        std::cout << "Enter your message (type 'exit' to quit): ";
        std::getline(std::cin, userMessage);
        if (userMessage == "exit")
            break;
        std::string gpt3Response = chatWithGpt3(userMessage);
        std::cout << "GPT-3 Response: " << gpt3Response << std::endl;
    }
    return 0;
}