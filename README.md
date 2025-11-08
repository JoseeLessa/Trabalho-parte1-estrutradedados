#  Gerenciador de Campeonato em C

Este projeto é uma aplicação de **console em C**, criada para **gerenciar e exibir estatísticas de um campeonato de futebol**.  
O sistema é capaz de ler dados de times e resultados de partidas, processar essas informações e apresentar um **placar de classificação**, além de permitir **consultas detalhadas**.


---

##  Visão Geral dos Recursos

- **Carregamento de Dados:** Lê e interpreta automaticamente os arquivos de times e partidas ao iniciar.  
- **Cálculo de Estatísticas:** Processa os resultados de todas as partidas para calcular em tempo real a pontuação, saldo de gols e V/E/D de cada time.  
- **Interface Interativa:** Um menu de console simples e direto para acessar todas as funcionalidades.  
- **Consulta de Times:** Permite buscar times por prefixo (sem diferenciar maiúsculas/minúsculas) e exibe suas estatísticas completas.  
- **Consulta de Partidas:** Lista todos os jogos em que um time (buscado por prefixo) participou.  
- **Tabela de Classificação:** Exibe uma tabela completa e formatada com o desempenho de todos os times no campeonato.

---

##  Arquitetura do Código

O projeto é estruturado de forma **modular**, separando a lógica principal, a interface e as funções utilitárias.

###  Arquivos Principais

#### `main.c`
**Propósito:** Ponto de entrada da aplicação.  
**Responsabilidades:**  
- Aloca a memória principal para os "bancos de dados" (`BDTeams`, `BDPartidas`).  
- Gerencia o menu interativo (loop principal).  
- Direciona o fluxo do usuário para as funções apropriadas.

#### `campeonato.h`
**Propósito:** O “contrato” do sistema.  
**Responsabilidades:**  
- Define as estruturas de dados centrais (`Team`, `Partida`, `BDTeams`, `BDPartidas`).  
- Declara os protótipos de todas as funções públicas implementadas em `campeonato.c`.

#### `campeonato.c`
**Propósito:** O “core” da aplicação.  
**Responsabilidades:**  
- Implementa toda a **lógica do programa**.  
- Carrega arquivos, calcula pontos, processa buscas e formata a tabela de classificação.
- Funções de exibição e UI do usuário estão nesse arquivo.

#### `utils.h`
**Propósito:** Caixa de ferramentas de utilitários.  
**Responsabilidades:**  
- Fornece funções `inline` otimizadas e seguras para manipulação de strings, como:  
  - `str_trim` — remove espaços.  
  - `safe_atoi` — conversão segura de string para `int`.  
  - `str_starts_with_case_insensitive` — comparação de prefixos ignorando maiúsculas/minúsculas.

#### `Makefile`
**Propósito:** Automação de build.  
**Responsabilidades:**  
- Compila todos os arquivos `.c` em objetos `.o` e vincula no executável final `campeonato_gronerjose`.  
- Inclui alvos para **compilar**, **executar** e **limpar** o projeto.

---

## Como Compilar e Executar

### 1. Requisitos
- Compilador **gcc**  
- Utilitário **make**

### 2. Compilação
No terminal, execute:
```bash
make
```
Isso criará o arquivo executável **`campeonato_gronerjose`**.

### 3. Execução

#### Método A — Via Makefile
Compila (se necessário) e executa o programa automaticamente:
```bash
make run
```

#### Método B — Manualmente
Execute o binário diretamente:
```bash
./campeonato_gronerjose
```

---

## 💡 Arquivos de Dados

O programa espera encontrar os seguintes arquivos **no mesmo diretório do executável**:

- `times.csv`
- `partidas_vazio.csv`
- `partidas_parcial.csv`
- `partidas_completo.csv`

> Os nomes e caminhos desses arquivos estão definidos em `main.c`.  
> Caso deseje usar outro arquivo, escolhar entre 1, 2 e 3 durante a execução do aplicativo.
> O arquivo `times.csv` é obrigatório para a execução do código, não podendo assim ser alterado.

---

##  Evolução do Projeto (Próximos Passos)

- [ ] **Implementar Ordenação:**  
  A tabela de classificação (opção 6) atualmente exibe os times por ID.  
  O próximo passo é ordená-la por **Pontos (PG)**, **Saldo de Gols (S)** e **Gols Marcados (GM)**.

- [ ] **Completar o Menu:**  
  Implementar as opções de menu ausentes (como 3, 4, 5) para **adicionar, editar ou remover times e partidas**.

- [ ] **Parâmetros de Linha de Comando:**  
  Modificar `main.c` para aceitar os nomes dos arquivos de times e partidas como argumentos de linha de comando:
  ```bash
  ./campeonato_gronerjose times.csv partidas.csv
  ```




---

📍 **Autores:** *José Otávio e Pedro Groner*  


