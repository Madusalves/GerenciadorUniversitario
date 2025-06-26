#include "crow.h"
#include <sstream>

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([]() {
        return R"(
            <html>
            <body>
                <h1>Cadastro de Pessoa</h1>
                <form action="/cadastro" method="POST">
                    Nome: <input type="text" name="nome"><br><br>
                    Idade: <input type="number" name="idade"><br><br>
                    <input type="submit" value="Cadastrar">
                </form>
            </body>
            </html>
        )";
        });

    CROW_ROUTE(app, "/cadastro").methods("POST"_method)([](const crow::request& req) {
        crow::query_string body_query(req.body);
        auto nome = body_query.get("nome");
        auto idade = body_query.get("idade");

        std::ostringstream os;
        os << "<html><body>";
        os << "<h1>Dados Cadastrados</h1>";
        os << "<p><strong>Nome:</strong> " << (nome ? nome : "não informado") << "</p>";
        os << "<p><strong>Idade:</strong> " << (idade ? idade : "não informado") << "</p>";
        os << "<a href='/'>Voltar</a>";
        os << "</body></html>";

        return crow::response(os.str());
        });

    app.port(18080).multithreaded().run();
}
