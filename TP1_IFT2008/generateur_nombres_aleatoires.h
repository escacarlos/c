#ifndef _GENRANDNUM_H_
#define _GENRANDNUM_H_

#if __cplusplus
extern "C" {
#endif

static const unsigned int ENTROPIE = 16807;

typedef struct GenerateurNombresAleatoires {
    unsigned int m_etat;
    unsigned int m_maxPlusUn;
} GenerateurNombresAleatoires;

struct GenerateurNombresAleatoires_args {
    unsigned int init;
    unsigned int max;
};

GenerateurNombresAleatoires *GenerateurNombresAleatoires_create(struct GenerateurNombresAleatoires_args *fargs);

int GenerateurNombresAleatoires_pige(GenerateurNombresAleatoires *myGen);

void GenerateurNombresAleatoires_args_init(struct GenerateurNombresAleatoires_args *args);

void GenerateurNombresAleatoires_destroy(GenerateurNombresAleatoires *myGen);

#if __cplusplus
}
#endif

#endif /*_GENRANDNUM_H_*/