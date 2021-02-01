//
// Created by demen on 30/01/2021.
//
/*  49
 * Nome: Daniele        Cognome: Pavan      matricola: 875435
 * Nome: Lorenzo        Cognome: Demenia    matricola: 880099
 * Nome: Duy Khiem      Cognome: Vo         matricola: 881997
 * Nome: Fahd           Cognome: Es Saleh   matricola: 882119
 */
/*
 Created by Sebastiano Vascon on 23/03/20.
*/

#include <stdio.h>
#include "ip_lib.h"
#include "bmp.h"

void ip_mat_show(ip_mat * t){
    unsigned int i,l,j;
    printf("Matrix of size %d x %d x %d (hxwxk)\n",t->h,t->w,t->k);
    for (l = 0; l < t->k; l++) {
        printf("Slice %d\n", l);
        for(i=0;i<t->h;i++) {
            for (j = 0; j < t->w; j++) {
                printf("%f ", get_val(t,i,j,l));
            }
            printf("\n");
        }
        printf("\n");
    }
}

void ip_mat_show_stats(ip_mat * t){
    unsigned int k;

    compute_stats(t);

    for(k=0;k<t->k;k++){
        printf("Channel %d:\n", k);
        printf("\t Min: %f\n", t->stat[k].min);
        printf("\t Max: %f\n", t->stat[k].max);
        printf("\t Mean: %f\n", t->stat[k].mean);
    }
}

ip_mat * bitmap_to_ip_mat(Bitmap * img){
    unsigned int i=0,j=0;

    unsigned char R,G,B;

    unsigned int h = img->h;
    unsigned int w = img->w;

    ip_mat * out = ip_mat_create(h, w,3,0);

    for (i = 0; i < h; i++)              /* rows */
    {
        for (j = 0; j < w; j++)          /* columns */
        {
            bm_get_pixel(img, j,i,&R, &G, &B);
            set_val(out,i,j,0,(float) R);
            set_val(out,i,j,1,(float) G);
            set_val(out,i,j,2,(float) B);
        }
    }

    compute_stats(out);

    return out;
}

Bitmap * ip_mat_to_bitmap(ip_mat * t){

    Bitmap *b = bm_create(t->w,t->h);

    unsigned int i, j;
    for (i = 0; i < t->h; i++)              /* rows */
    {
        for (j = 0; j < t->w; j++)          /* columns */
        {
            bm_set_pixel(b, j,i, (unsigned char) get_val(t,i,j,0),
                         (unsigned char) get_val(t,i,j,1),
                         (unsigned char) get_val(t,i,j,2));
        }
    }
    return b;
}

float get_val(ip_mat * a, unsigned int i,unsigned int j,unsigned int k){
    if(i<a->h && j<a->w &&k<a->k){
        return a->data[i][j][k];
    }else{
        printf("Errore get_val!!!");
        exit(1);
    }
}

void set_val(ip_mat * a, unsigned int i,unsigned int j,unsigned int k, float v){
    if(i<a->h && j<a->w &&k<a->k){
        a->data[i][j][k]=v;
    }else{
        printf("Errore set_val!!!");
        exit(1);
    }
}

float get_normal_random(float media, float std){

    float y1 = ( (float)(rand()) + 1. )/( (float)(RAND_MAX) + 1. );
    float y2 = ( (float)(rand()) + 1. )/( (float)(RAND_MAX) + 1. );
    float num = cos(2*PI*y2)*sqrt(-2.*log(y1));

    return media + num*std;
}
/**** PARTE 1: TIPO DI DATI ip_mat E MEMORIA ****/
/* Inizializza una ip_mat con dimensioni h w e k. Ogni elemento è inizializzato a v.
 * Inoltre crea un vettore di stats per contenere le statische sui singoli canali.
 */
ip_mat * ip_mat_create(unsigned int h, unsigned int w,unsigned  int k, float v)
{
    unsigned int i,j,u; /*indici per scorrere*/
    ip_mat *pointer; /*puntatore alla struttura ip_mat*//*
    stats *stat; puntatore alla struttura stats*/
    /*NB: stat punta ad un vettore di stats, quindi ogni cella di tale vettore è una struttura di tipo stats (con: min, max, mean)*/

    pointer = (ip_mat*) malloc(sizeof(ip_mat)); /*alloco memoria dinamica per il puntatore (quindi "creo" la struttura ip_mat)*/
    assert(pointer != NULL); /*controllo che l'allocazione sia andata a buon fine*/

    pointer->data = (float***) malloc(sizeof(float**) * h);/*inizio a creare la matrice 3D: creo un vettore verticale (dim=h)*/
    assert(pointer->data != NULL);

    for(i=0; i<h; i++){
        pointer->data[i] = (float**) malloc(sizeof(float*) * w);/*ogni cella del vettore verticale punta ad un vettore orizzontale(dim=w)*/
        assert(pointer->data[i] != NULL);
    }
    /*a questo punto ho creato una matrice 2D (griglia)*/
    for(i=0; i<h; i++){
        for(j=0; j<w; j++){
            pointer->data[i][j] = (float*) malloc(sizeof(float) * k);/*ogni cella di ogni vettore orizzontale punta ad un vettore "obliquo", cioè il canale*/
            assert(pointer->data[i][j] != NULL);
        }
    }
    /* a questo punto ho creato la matrice 3D, "data" */
    for(i=0; i<h; i++){
        for(j=0; j<w; j++){
            for(u=0; u<k; u++){
                pointer->data[i][j][u] = v;/*assegno un valore v ad ogni elemento della matrice*/
            }
        }
    }
    /*creo, nella struttura, le variabili che determinano le dimensioni della matrice*/
    pointer->h = h;
    pointer->w = w;
    pointer->k = k;

    /*alloco mem dinamica per il puntatore stat (che punta ad una struttura di tipo stats)*/
    pointer->stat = (stats *) malloc(sizeof(stats) * k);
    assert(pointer->stat != NULL);

    for(i=0; i<k; i++){
        pointer->stat[i].min = 0.0;
        pointer->stat[i].max = 0.0;
        pointer->stat[i].mean = 0.0;
    }
    return pointer;
}

/* Libera la memoria (data, stat e la struttura) */
void ip_mat_free(ip_mat *a)
{
    if(a != NULL){
        unsigned int i,j;

        for(i=0; i<(a->h); i++){
            for(j=0; j<(a->w); j++){
                free(a->data[i][j]);
            }
        }
        for(i=0; i<(a->h); i++){
            free(a->data[i]);
        }

        free(a->data);
        free(a->stat);
        free(a);
    }
}

/* Calcola il valore minimo, il massimo e la media per ogni canale e li salva dentro la struttura ip_mat stats */
void compute_stats(ip_mat *t)
{
    if(t != NULL){
        unsigned int i,j,u;
        float minimo,massimo,media,count,somma;

        for(u=0; u<(t->k); u++){ /*perchè ci sono 3 canali totali, così calcolo: min,max,mean per ogni canale di tutta la struttura*/
            somma = 0.0;
            media = 0.0;
            count = 0.0;
            i=0;
            j=0;
            minimo = t->data[i][j][u];
            massimo = t->data[i][j][u];

            for(i=0; i<(t->h); i++){
                for(j=0; j<(t->w); j++){
                    if(t->data[i][j][u] > massimo){
                        massimo = t->data[i][j][u];
                    }
                    if(t->data[i][j][u] < minimo){
                        minimo = t->data[i][j][u];
                    }
                    count += t->data[i][j][u];
                    somma++;
                }
            }
            /*ora ho calcolato min,max,mean per il m-esimo canale*/
            media = count/somma;

            t->stat[u].min = minimo;
            t->stat[u].max = massimo;
            t->stat[u].mean = media;
        }
    }
    else{
        printf("Errore: ip_mat in ingresso è NUll!\n\n");
        exit(1);
    }
}

/* Inizializza una ip_mat con dimensioni w h e k.
 * Ogni elemento è generato da una gaussiana con media mean e deviazione std */
void ip_mat_init_random(ip_mat * t, float mean, float std)
{
    if(t != NULL){
        unsigned int i,j,u;

        for(i=0; i<(t->h); i++){
            for(j=0; j<(t->w); j++){
                for(u=0; u<(t->k); u++){
                    t->data[i][j][u] = get_normal_random(mean,std);
                }
            }
        }
    }
    else{
        printf("Errore: ip_mat in ingresso è NUll!\n\n");
        exit(1);
    }
}

/* Crea una copia di una ip_mat e lo restituisce in output */
ip_mat * ip_mat_copy(ip_mat * in)
{
    if(in != NULL){
        unsigned int i,j,u; /*indici per scorrere*/
        ip_mat *pointer; /*puntatore alla struttura ip_mat*/

        pointer = ip_mat_create((in->h),(in->w),(in->k),0.0);

        for(i=0; i<(in->h); i++){
            for(j=0; j<(in->w); j++){
                for(u=0; u<(in->k); u++){
                    pointer->data[i][j][u] = in->data[i][j][u]; /*copia dei valori dell'ip_mat*/
                }
            }
        }
        compute_stats(pointer);

        return pointer;
    }
    else{
        printf("Errore: ip_mat in ingresso è NUll!\n\n");
        exit(1);
    }
}

/* Restituisce una sotto-matrice, ovvero la porzione individuata da:
 * t->data[row_start...row_end][col_start...col_end][0...k]
 * La terza dimensione la riportiamo per intero, stiamo in sostanza prendendo un sottoinsieme delle righe e delle colonne.
 */
ip_mat * ip_mat_subset(ip_mat * t, unsigned int row_start, unsigned int row_end, unsigned int col_start, unsigned int col_end)
{
    if(t != NULL){
        unsigned int i,j,u; /*indici per scorrere la sottomatrice*/
        unsigned int x,y,z; /*indici per scorrere la matrice originale*/
        unsigned int dim_h, dim_w, dim_k; /*dimensioni della sottomatrice*/
        ip_mat *pointer; /*puntatore alla struttura con la sottomatrice*/

        dim_h = (row_end - row_start); /*escluso row_end*/
        dim_w = (col_end - col_start); /*escluso col_end*/
        dim_k = t->k;

        pointer = ip_mat_create(dim_h, dim_w, dim_k, 0.0);

        for(i=0; i<dim_h; i++){
            for(j=0; j<dim_w; j++){
                for(u=0; u<dim_k; u++){
                    x = i+row_start;
                    y = j+col_start;
                    z = u;
                    pointer->data[i][j][u] = t->data[x][y][z];
                    /*ad ogni cella della mia sottomatrice(puntata da under) assegno il valore della corrispondente cella della matrice originale*/
                }
            }
        }
        compute_stats(pointer);

        return pointer;
    }
    else{
        printf("Errore: ip_mat in ingresso è NUll!\n\n");
        exit(1);
    }
}

/* Concatena due ip_mat su una certa dimensione.
 * Ad esempio:
 * ip_mat_concat(ip_mat * a, ip_mat * b, 0);
 *      produrrà un nuovo ip_mat di dimensioni:
 *      out.h = a.h + b.h
 *      out.w = a.w = b.w
 *      out.k = a.k = b.k
 *
 * ip_mat_concat(ip_mat * a, ip_mat * b, 1);
 *      produrrà un nuovo ip_mat di dimensioni:
 *      out.h = a.h = b.h
 *      out.w = a.w + b.w
 *      out.k = a.k = b.k
 *
 * ip_mat_concat(ip_mat * a, ip_mat * b, 2);
 *      produrrà un nuovo ip_mat di dimensioni:
 *      out.h = a.h = b.h
 *      out.w = a.w = b.w
 *      out.k = a.k + b.k
 */
ip_mat * ip_mat_concat(ip_mat * a, ip_mat * b, int dimensione)
{
    if(a != NULL && b != NULL){
        ip_mat *pointer;
        unsigned int i,j,u;

        if(a->k == b->k && a->w == b->w && a->h == b->h)
        {
            pointer = (ip_mat *) malloc(sizeof(ip_mat));
            assert(pointer != NULL);

            if(dimensione == 0){
                pointer->h = a->h + b->h;
                pointer->w = a->w;
                pointer->k = a->k;

                pointer = ip_mat_create((pointer->h),(pointer->w),(pointer->k),0.0);

                for(i=0; i<(a->h); i++){
                    for(j=0; j<(pointer->w); j++){
                        for(u=0; u<(pointer->k); u++){
                            pointer->data[i][j][u] = a->data[i][j][u];
                        }
                    }
                }
                for(i=(a->h); i<(pointer->h); i++){
                    for(j=0; j<(pointer->w); j++){
                        for(u=0; u<(pointer->k); u++){
                            pointer->data[i][j][u] = b->data[i-(a->h)][j][u];
                        }
                    }
                }
            }
            else{
                if(dimensione == 1){
                    pointer->h = a->h;
                    pointer->w = a->w + b->w;
                    pointer->k = a->k;

                    pointer = ip_mat_create((pointer->h),(pointer->w),(pointer->k),0.0);

                    for(j=0; j<(a->w); j++){
                        for(i=0; i<(pointer->h); i++){
                            for(u=0; u<(pointer->k); u++){
                                pointer->data[i][j][u] = a->data[i][j][u];
                            }
                        }
                    }
                    for(j=(a->w); j<(pointer->w); j++){
                        for(i=0; i<(pointer->h); i++){
                            for(u=0; u<(pointer->k); u++){
                                pointer->data[i][j][u] = b->data[i][j-(a->w)][u];
                            }
                        }
                    }
                }
                else{
                    pointer->h = a->h;
                    pointer->w = a->w;
                    pointer->k = a->k + b->k;

                    pointer = ip_mat_create((pointer->h),(pointer->w),(pointer->k),0.0);

                    for(u=0; u<(a->k); u++){
                        for(i=0; i<(pointer->h); i++){
                            for(j=0; j<(pointer->w); j++){
                                pointer->data[i][j][u] = a->data[i][j][u];
                            }
                        }
                    }
                    for(u=(a->k); u<(pointer->k); u++){
                        for(i=0; i<(pointer->h); i++){
                            for(j=0; j<(pointer->w); j++){
                                pointer->data[i][j][u] = b->data[i][j][u-(a->k)];
                            }
                        }
                    }
                }
            }
            compute_stats(pointer);
        }
        else{
            printf("Errore tutte le dimensioni devono essere identiche!!!\n\n");
            exit(1);
        }
        return pointer;
    }
    else{
        printf("Errore: ip_mat in ingresso è NUll!\n\n");
        exit(1);
    }
}

/**** PARTE 1: OPERAZIONI MATEMATICHE FRA IP_MAT ****/
/* Esegue la somma di due ip_mat (tutte le dimensioni devono essere identiche) e la restituisce in output. */
ip_mat * ip_mat_sum(ip_mat * a, ip_mat * b)
{
    if(a != NULL && b != NULL){
        unsigned int i,j,u;
        ip_mat *pointer;

        if(a->k == b->k && a->w == b->w && a->h == b->h) /*stessa dimensione*/
        {
            pointer = ip_mat_create((a->h),(a->w),(a->k),0.0);

            for(i=0; i<(a->h); i++){
                for(j=0; j<(a->w); j++){
                    for(u=0; u<(a->k); u++){
                        pointer->data[i][j][u] = ((a->data[i][j][u])+(b->data[i][j][u])); /*sommo i valori di a con b*/
                    }
                }
            }
            compute_stats(pointer);
        }
        else{
            printf("Errore tutte le dimensioni devono essere identiche!!!\n\n");
            exit(1);
        }
        return pointer;
    }
    else{
        printf("Errore: ip_mat in ingresso è NUll!\n\n");
        exit(1);
    }
}

/* Esegue la sottrazione di due ip_mat (tutte le dimensioni devono essere identiche) e la restituisce in output.*/
ip_mat * ip_mat_sub(ip_mat * a, ip_mat * b)
{
    if(a != NULL && b != NULL){
        unsigned int i,j,u;
        ip_mat *pointer;

        if(a->k == b->k && a->w == b->w && a->h == b->h)  /*stessa dimensione*/
        {
            pointer = ip_mat_create((a->h),(a->w),(a->k),0.0);

            for(i=0; i<(a->h); i++){
                for(j=0; j<(a->w); j++){
                    for(u=0; u<(a->k); u++){
                        pointer->data[i][j][u] = ((a->data[i][j][u])-(b->data[i][j][u])); /*sottraggo i valori di a con b*/
                    }
                }
            }
            compute_stats(pointer);
        }
        else{
            printf("Errore tutte le dimensioni devono essere identiche!!!\n\n");
            exit(1);
        }
        return pointer;
    }
    else{
        printf("Errore: ip_mat in ingresso è NUll!\n\n");
        exit(1);
    }
}

/* Moltiplica un ip_mat per uno scalare c.
 * Si moltiplica c per tutti gli elementi di "a" e si salva il risultato in un nuovo tensore in output.
 */
ip_mat * ip_mat_mul_scalar(ip_mat *a, float c)
{
    if(a != NULL){
        unsigned int i,j,u;
        ip_mat *pointer;

        pointer = ip_mat_create((a->h),(a->w),(a->k),0.0);

        for(i=0; i<(a->h); i++){
            for(j=0; j<(a->w); j++){
                for(u=0; u<(a->k); u++){
                    pointer->data[i][j][u] = ((a->data[i][j][u]) * c);
                }
            }
        }
        compute_stats(pointer);

        return pointer;
    }
    else{
        printf("Errore: ip_mat in ingresso è NUll!\n\n");
        exit(1);
    }
}

/* Aggiunge ad un ip_mat uno scalare c e lo restituisce in un nuovo tensore in output. */
ip_mat * ip_mat_add_scalar(ip_mat *a, float c)
{
    if(a != NULL){
        unsigned int i,j,u;
        ip_mat *pointer;

        pointer=ip_mat_create((a->h),(a->w),(a->k),0.0);

        for(i=0; i<(a->h); i++){
            for(j=0; j<(a->w); j++){
                for(u=0; u<(a->k); u++){
                    pointer->data[i][j][u] = ((a->data[i][j][u]) + c); /*sommo i valori di a con b e li divido per 2*/
                }
            }
        }
        compute_stats(pointer);

        return pointer;
    }
    else{
        printf("Errore: ip_mat in ingresso è NUll!\n\n");
        exit(1);
    }
}

/* Calcola la media di due ip_mat a e b e la restituisce in output.*/
ip_mat * ip_mat_mean(ip_mat * a, ip_mat * b)
{
    if(a != NULL && b != NULL){
        unsigned int i,j,u;
        ip_mat *pointer;

        if(a->k == b->k && a->w == b->w && a->h == b->h)  /*controlla che abbiano la stessa dimensione*/
        {
            pointer = ip_mat_create((a->h),(a->w),(a->k),0.0);

            for(i=0;i<(a->h);i++){
                for(j=0;j<(a->w);j++){
                    for(u=0;u<(a->k);u++){
                        pointer->data[i][j][u] = (((a->data[i][j][u])+(b->data[i][j][u]))/2.0); /*sommo i valori di a con b e li divido per 2*/
                    }
                }
            }
            compute_stats(pointer);
        }
        else{
            printf("Errore tutte le dimensioni devono essere identiche!!!\n\n");
            exit(1);
        }
        return pointer;
    }
    else{
        printf("Errore: ip_mat in ingresso è NUll!\n\n");
        exit(1);
    }
}

/**** PARTE 2: SEMPLICI OPERAZIONI SU IMMAGINI ****/
/* Converte un'immagine RGB ad una immagine a scala di grigio.
 * Quest'operazione viene fatta calcolando la media per ogni pixel sui 3 canali
 * e creando una nuova immagine avente per valore di un pixel su ogni canale la media appena calcolata.
 * Avremo quindi che tutti i canali saranno uguali.
 */
ip_mat * ip_mat_to_gray_scale(ip_mat * in)
{
    if(in != NULL){
        unsigned int i,j,u;
        ip_mat *pointer;

        pointer = ip_mat_create((in->h),(in->w),(in->k),0.0); /*creo la mia matrice di output*/

        for(i=0; i<(in->h); i++){
            for(j=0; j<(in->w); j++){
                for(u=0; u<(in->k); u++){
                    /*calcola la media per ogni canale di in e la salva in ogni pixel di pointer, in questo modo in ha lo stesso valore in
                    ogni canale, quindi non ha combinazioni di colori diversi, pertanto ha lo stesso colore (grigio) dappertutto*/
                    pointer->data[i][j][u] = ((in->data[i][j][0] + in->data[i][j][1] + in->data[i][j][2]) / 3);
                }
            }
        }
        compute_stats(pointer);

        return pointer;
    }
    else{
        printf("Errore: ip_mat in ingresso è NUll!\n\n");
        exit(1);
    }
}

/* Effettua la fusione (combinazione convessa) di due immagini.
 *
 * I parametri della funzione non subiscono modiche, il risultato viene salvato e restituito in output
 * all'interno di una nuova ip_mat.
 */
ip_mat * ip_mat_blend(ip_mat * a, ip_mat * b, float alpha)
{
    if(a != NULL && b != NULL){
        unsigned int i,j,u;
        ip_mat *pointer;

        if((alpha >= 0.0) && (alpha <= 1.0) && (a->h == b->h) && (a->w == b->w) && (a->k == b->k))
        {
            pointer = ip_mat_create(a->h,a->w,a->k,0.0);

            for(i=0; i<(a->h); i++){
                for(j=0; j<(a->w); j++){
                    for(u=0; u<(a->k); u++){ /*Formula: aplha * A + (1-aplha) * B*/
                        pointer->data[i][j][u] = (alpha * (a->data[i][j][u])) + (1-alpha) * (b->data[i][j][u]);

                    }
                }
            }
            compute_stats(pointer);
        }
        else{
            printf("Dimensioni diverse o alpha non compreso tra 0 e 1\n\n");
            exit(1);
        }
        return pointer;
    }
    else{
        printf("Errore: ip_mat in ingresso è NUll!\n\n");
        exit(1);
    }
}

/* Operazione di brightening: aumenta la luminosità dell'immagine aggiunge ad ogni pixel un certo valore
 *
 * I parametri della funzione non subiscono modiche, il risultato viene salvato e restituito in output
 * all'interno di una nuova ip_mat.
 */
ip_mat * ip_mat_brighten(ip_mat * a, float bright)
{
    if(a != NULL){
        ip_mat *pointer;
        pointer = ip_mat_add_scalar(a,bright); /*aggiunge ad a lo scalare bright*/

        compute_stats(pointer);

        return pointer;
    }
    else{
        printf("Errore: ip_mat in ingresso è NUll!\n\n");
        exit(1);
    }
}

/* Operazione di corruzione con rumore gaussiano:
 * Aggiunge del rumore gaussiano all'immagine, il rumore viene enfatizzato per mezzo della variabile amount.
 *
 * out = a + gauss_noise*amount
 *
 * I parametri della funzione non subiscono modifiche, il risultato viene salvato e restituito in output all'interno di una nuova ip_mat.
 * NBq: determinare la varianza e mean a partire da amount
 */
ip_mat * ip_mat_corrupt(ip_mat *a, float amount)
{
    if(a != NULL){
        ip_mat *pointer; /*puntatore alla nuova ip_mat*/

        float media = 0.0; /*media == mean*/
        float std = amount/2; /*deviazione standard*/
        unsigned int i,j,u; /*indici*/
        float r;

        pointer = ip_mat_create((a->h),(a->w),(a->k),0.0);

        for(i=0; i<(a->h); i++){
            for(j=0; j<(a->w); j++){
                for(u=0; u<(a->k); u++){
                    r = get_normal_random(media, std);
                    pointer->data[i][j][u] = a->data[i][j][u] + r;
                }
            }
        }
        compute_stats(pointer);

        return pointer;
    }
    else{
        printf("Errore: ip_mat in ingresso è NUll!\n\n");
        exit(1);
    }
}

/**** PARTE 3: CONVOLUZIONE E FILTRI *****/
/* Effettua la convoluzione di un ip_mat "a" con un ip_mat "f".
 * La funzione restituisce un ip_mat delle stesse dimensioni di "a".
 *
 * I parametri della funzione non subiscono modiche, il risultato viene salvato e restituito in output
 * all'interno di una nuova ip_mat.
 */
ip_mat * ip_mat_convolve(ip_mat * a, ip_mat * f)
{
    if(a != NULL && f != NULL){
        unsigned int i,j,u;
        unsigned int z,b;
        float somma = 0.0; /*accumulatore*/

        ip_mat * output;
        ip_mat * padding;

        /*Formula per il padding: P = (F-1)/2 */
        unsigned int pad_h = ((f->h)-1)/2; /*trovo i valori verticali per padding*/
        unsigned int pad_w = ((f->w)-1)/2; /*trovo i valori laterali per padding*/

        padding = ip_mat_padding(a,pad_h,pad_w); /*genero la matrice con il padding*/
        output = ip_mat_create((a->h),(a->w),(a->k),0.0); /*creo la ip_mat di output(data è senza padding)*/

        for(u=0; u<(a->k); u++){ /*canale*/
            for(j=0; j<(a->w); j++){
                for(i=0; i<(a->h); i++){ /*shifta a destra*/
                    for(z=0; z<(f->h); z++){ /*scorre il filtro in altezza(height)*/
                        for(b=0; b<(f->w); b++){ /*scorre il filtro in lunghezza(width)*/
                            somma += (padding->data[z+i][b+j][u]) * (f->data[z][b][0]);
                        }
                    }
                    output->data[i][j][u] = somma;
                    somma = 0.0;
                }
            }
        }
        ip_mat_free(padding); /*libero la memoria dall'ip_mat "padding" usata per la convoluzione*/
        compute_stats(output);

        return output; /*ritorno l'immagine filtrata*/
    }
    else{
        printf("Errore: ip_mat in ingresso è NUll!\n\n");
        exit(1);
    }
}

/* Aggiunge un padding all'immagine. Il padding verticale è pad_h mentre quello orizzontale è pad_w.
 * L'output sarà un'immagine di dimensioni:
 *      out.h = a.h + 2*pad_h;
 *      out.w = a.w + 2*pad_w;
 *      out.k = a.k
 * con valori nulli sui bordi corrispondenti al padding e l'immagine "a" riportata nel centro.
 *
 * I parametri della funzione non subiscono modiche, il risultato viene salvato e restituito in output all'interno di una nuova ip_mat.
 */
ip_mat * ip_mat_padding(ip_mat * a, unsigned int pad_h, unsigned int pad_w)
{
    if(a != NULL){
        ip_mat * pointer;
        unsigned int i,j,u;
        unsigned int h,w;

        h = (a->h) + 2 * pad_h; /*sto creando la dimensione dell'immagine, in h*/
        w = (a->w) + 2 * pad_w; /*sto creando la dimensione dell'immagine , in w*/
        /*NB: moltiplico per 2 poichè ho una matrice quadrata, quindi ho bordo sia sopra che sotto*/

        pointer = ip_mat_create(h,w,(a->k),0.0); /*creo la mia ip_mat di output con dimensioni di data uguali alle dimensioni di a + padding*/

        for(u=0; u<(a->k); u++){ /*per ogni canale*/
            for(i=0; i<(a->h); i++){
                for(j=0; j<(a->w); j++){
                    pointer->data[i+pad_h][j+pad_w][u] = a->data[i][j][u];
                }
            }
        }
        compute_stats(pointer);

        return pointer;
    }
    else{
        printf("Errore: ip_mat in ingresso è NUll!\n\n");
        exit(1);
    }
}

/* Crea un filtro di sharpening (permette di enfatizzare i dettagli) */
ip_mat * create_sharpen_filter()
{
    unsigned int i,j;
    ip_mat * pointer;

    pointer = ip_mat_create(3,3,1,0.0);

    for(i=0; i<(pointer->h); i++){
        for(j=0; j<(pointer->w); j++){
            if(i==1 && j==1){
                pointer->data[i][j][0] = 5.0;
            }
            else{
                if(i==1 || j==1)
                    pointer->data[i][j][0] = -1.0;
            }
        }
    }
    compute_stats(pointer);

    return pointer;
}

/* Crea un filtro per rilevare i bordi (calcola i contorni dell'immagine) */
ip_mat * create_edge_filter()
{
    unsigned int i,j;
    ip_mat *pointer;

    pointer = ip_mat_create(3,3,1,0.0);

    for(i=0; i<(pointer->h); i++){
        for(j=0; j<(pointer->w); j++){
            if(i==1 && j==1){
                pointer->data[i][j][0] = 8.0;
            }
            else{
                pointer->data[i][j][0] = -1.0;
            }
        }
    }
    compute_stats(pointer);

    return pointer;
}

/* Crea un filtro per aggiungere profondità */
ip_mat * create_emboss_filter()
{
    unsigned int i,j;
    ip_mat *pointer;
    pointer = ip_mat_create(3,3,1,0.0);

    for(i=0; i<(pointer->h); i++){
        for(j=0; j<(pointer->w); j++){
            if(i==0 && j==0){
                pointer->data[i][j][0] = -2.0;
            }
            else{
                if((i==0 && j==1) || (i==1 && j==0)){
                    pointer->data[i][j][0] = -1.0;
                }
                else{
                    if((i==1 && j==1) || (i==1 && j==2) || (i==2 && j==1)){
                        pointer->data[i][j][0] = 1.0;
                    }
                    else{
                        if(i==2 && j==2){
                            pointer->data[i][j][0] = 2.0;
                        }
                    }
                }
            }
        }
    }
    compute_stats(pointer);

    return pointer;
}

/* Crea un filtro medio per la rimozione del rumore (permette di rimuovere il rumore).
 *
 * c = 1/(w*h)
 */
ip_mat * create_average_filter(unsigned int h, unsigned int w, unsigned int k)
{
    float c = 1.0/(w * h);
    ip_mat *pointer;

    pointer = ip_mat_create(3,3,1,c);

    compute_stats(pointer);

    return pointer;
}

/* Crea un filtro gaussiano per la rimozione del rumore */
ip_mat * create_gaussian_filter(unsigned int h, unsigned int w, unsigned int k, float sigma)
{
    ip_mat * pointer;
    unsigned int i,j,u;
    unsigned int cx = w/2, cy = h/2; /*calcolo le coordinate della cella centrale del filtro*/
    unsigned int x,y;
    float sum = 0.0; /*accumulatore*/

    pointer = ip_mat_create(h,w,k,0.0);

    for(u=0; u<k; u++){
        for(i=0; i<h; i++){
            for(j=0; j<w; j++){
                x = i-cx;
                y = j-cy; /*distanza della cella (i,j) rispetto al centro*/
                pointer->data[i][j][u] = (1/(2*PI*(sigma*sigma)))*(exp(-(((x*x)+(y*y))/(2*(sigma*sigma)))));
                sum += pointer->data[i][j][u];
            }
        }
        for(i=0; i<h; i++){
            for(j=0; j<w; j++){
                pointer->data[i][j][u] /= sum;
            }
        }
    }
    compute_stats(pointer);

    return pointer;
}

/* Effettua una riscalatura dei dati tale che i valori siano in [0,new_max].
 * Utilizzate il metodo compute_stat per ricavarvi il min, max per ogni canale.
 *
 * I valori sono scalati tramite la formula (valore - min)/(max - min)
 *
 * Si considera ogni indice della terza dimensione indipendente, quindi l'operazione
 * di scalatura va ripetuta per ogni "fetta" della matrice 3D.
 * Successivamente moltiplichiamo per new_max gli elementi della matrice in modo da ottenere un range di valori in [0,new_max].
 *
 * Il risultato dell'operazione si salva in t
 */
void rescale(ip_mat * t, float new_max)
{
    if(t != NULL){
        unsigned int i,j,u;
        float range;

        compute_stats(t); /*calcola min,max e media per ogni canale e li salva dentro ip_mat stats*/

        for(u=0; u<(t->k);u++){
            if((t->stat[u].max) != (t->stat[u].min)){
                for(i=0; i<(t->h); i++){
                    for(j=0; j<(t->w); j++){/*Formula: (val - min)/(max - min) */
                        range = (t->stat[u].max) - (t->stat[u].min);
                        t->data[i][j][u] = ((t->data[i][j][u])-(t->stat[u].min)) / range;
                        t->data[i][j][u] = t->data[i][j][u] * new_max;
                    }
                }
            }
        }
    }
    else{
        printf("Errore: ip_mat in ingresso è NUll!\n\n");
        exit(1);
    }
}

/* Nell'operazione di clamping i valori <low si convertono in low e i valori >high in high.
 *
 * Il risultato dell'operazione si salva in t
 */
void clamp(ip_mat * t, float low, float high)
{
    if(t != NULL){
        unsigned int i,j,u;

        compute_stats(t);

        for(i=0; i<(t->h); i++){
            for(j=0; j<(t->w); j++){
                for(u=0; u<(t->k); u++){
                    if((t->data[i][j][u]) < low){
                        t->data[i][j][u] = low;
                    }
                    if((t->data[i][j][u]) > high){
                        t->data[i][j][u] = high;
                    }
                }
            }
        }
    }
    else{
        printf("Errore: ip_mat in ingresso è NUll!\n\n");
        exit(1);
    }
}
