typedef struct smapa Mapa;

Mapa* m_cria (void);
Mapa* m_insere (Mapa* m, int chave, int novodado);
int m_busca (Mapa *m, int chave);
Mapa* m_remove (Mapa *m, int chave);
void m_destroi (Mapa *m);

void m_debugMostraMapa(Mapa* map); //Função de testes