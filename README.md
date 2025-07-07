

# 📦 Inicialização e Execução do Projeto

Este guia descreve o passo a passo necessário para clonar, compilar e executar o projeto localmente em um ambiente Windows.

## 🚀 Etapas de Execução

### 1️⃣ Clonar o repositório

Abra o terminal (CMD, PowerShell ou Git Bash) e execute:

```bash
git clone https://github.com/Madusalves/GerenciadorUniversitario.git
```


---

### 2️⃣ Executar o script `.bat` de configuração

Navegue até a pasta do projeto e execute o script `.bat`:

```bash
cd GerenciadorUniversitario
.\setup.bat
```

> O script pode instalar dependências ou configurar variáveis de ambiente, dependendo da sua implementação.

---

### 3️⃣ Acessar o diretório de build

Após a execução do script, entre na pasta `build` gerada:

```bash
cd build
```

---

### 4️⃣ Compilar o projeto com CMake

Execute o comando para compilar o projeto:

```bash
cmake --build .
```

Esse comando utilizará os arquivos de configuração CMake para compilar o projeto de acordo com o compilador e build system configurado.

---

## 🧪 Execução da aplicação

Após a compilação, o executável estará disponível na pasta `build`. Basta rodá-lo diretamente:

```bash
./NomeDoExecutavel.exe
```

> Substitua `NomeDoExecutavel.exe` pelo nome real gerado pela compilação.

---

## ❓ Suporte

Se você encontrar qualquer problema durante a configuração ou execução do projeto, abra uma [issue](https://github.com/seu-usuario/seu-repositorio/issues) ou entre em contato diretamente.

---

<br>





# - Trabalho Acadêmico em C++

Este projeto foi desenvolvido como parte de um trabalho acadêmico em C++, com o objetivo de praticar a manipulação de entradas e saídas de dados, uso de estruturas condicionais, laços de repetição, vetores, funções e outros recursos fundamentais da linguagem.

## Recursos e Funções Utilizadas

### 📌 `cin.ignore()`
A função `cin.ignore()` é utilizada para ignorar caracteres restantes no buffer de entrada. É especialmente útil quando misturamos diferentes tipos de entrada, como `cin >>` (para strings ou números) seguido de `getline()` (para ler uma linha inteira). 

Quando usamos `cin >>`, o caractere `\n` (ENTER) que o usuário digita ao final da entrada permanece no buffer, e isso pode interferir em leituras subsequentes.

Exemplo: 
```char teste[20];
std::cin >> teste;
std::cin.ignore(); // Ignora o '\n' que ficou no buffer
```
 [`Referência`](https://en.cppreference.com/w/cpp/io/basic_istream/ignore) Programar em C++/Entrada e saída de dados

 ### 📌 `push_back()`
 A função push_back() é usada com vetores dinâmicos em C++ (std::vector). Ela serve para adicionar um novo elemento ao final do vetor, expandindo seu tamanho automaticamente.
 ```
int main() {
    std::vector<int> numeros;

    numeros.push_back(10);
    numeros.push_back(20);
    numeros.push_back(30);

    for (int n : numeros) {
        std::cout << n << " ";
    }
    // Saída: 10 20 30
}
```
 <br> [`Referência`](https://www.geeksforgeeks.org/cpp/vector-push-back-cpp-stl/) cppreference.com <br>
 [`Referência`](https://en.cppreference.com/w/cpp/container/vector/push_back) geeksforgeeks

  ### 📌 `auto (c++)`
  A palavra-chave auto declara uma variável cujo tipo é deduzido da expressão de inicialização na declaração.

  Quando `auto` é usado para declarar o parâmetro loop em uma instrução for baseada em intervalo, ele usa uma sintaxe de inicialização diferente, por exemplo, for (auto& i : iterable) do_action(i);. Para obter mais informações, consulte Instrução for baseada em intervalo (C++).
  
  
  <br>[`Referência`](https://learn.microsoft.com/pt-br/cpp/cpp/auto-cpp?view=msvc-170) auto (C++) | Microsoft Learn
  <br> [`Referência`](https://learn.microsoft.com/pt-br/cpp/cpp/range-based-for-statement-cpp?view=msvc-170) Instrução for com base em intervalo (C++) | Microsoft Learn


  ### 📌 `Uso de & (Referência)`
Em C++, o símbolo & é usado para passar uma variável por referência, ou seja, sem criar uma cópia dela. Quando usamos &, estamos dizendo ao programa para trabalhar diretamente com o dado original, e não com uma cópia.
 <br>[`Referência`](https://en.cppreference.com/w/cpp/language/reference.html) cppreference.com
