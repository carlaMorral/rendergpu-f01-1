# RenderGPU
Segona pràctica de GiVD 2020-21
    
**Abstract**

*(NOTA: Petit resum del què heu fet, no més de 200 paraules)*

**Features**

*(NOTA: Quines parts heu desenvolupat i qui ho ha fet de l'equip. Editeu la llista que teniu a continuació afegint darrera de cada punt, la/es persona/es que ha treballat en aquell punt.)*

- Fase 1
    - Adaptació a la lectura de fitxers de dades
        - [ ] Objectes
        - [ ] Escenes virtuals
        - [ ] Escenes de dades Reals 
    - Material: *Martí*
    - Light
        - [ ] Puntual
        - [ ] Direccional
        - [ ] Spotlight
        - [ ] Ambient Global
    - Shading
        - [ ] Phong
        - [ ] Gouraud
    - Textures
        - [ ] Textura com material en un objecte
        - [ ] Textura al pla base
        

- Fase 2 (OPT)
    - [ ] Toon-shading i èmfasi de siluetes
    - [ ] Mapping indirecte de textures
    - [ ] Animacions amb dades temporals
    - [ ] Normal mapping
    - [ ] Entorn amb textures
    - [ ] Reflexions
    - [ ] Transparencias via objectes.
    - [ ] Transparencias via environmental mapping.


## Extensions

*(NOTA: Les extensions de la pràctica que heu fet i que no surten a la llista anterior)*

## Memòria

*(NOTA: Explicació només dels diferents punts que heu desenvolupat i funcionen, detallant les estratègies que heu fet servir)*

## Screenshots

*(NOTA: Per a cada pas de l'enunciat (del 1 al 6), incloure captures de pantalla de les proves que heu fet per a demostrar la funcionalitat de la vostra pràctica amb explicacions de la seva configuració i com les heu aconseguides)*

### Pas 1

### Pas 2

Per a comprovar que el pas de les característiques del material de la CPU a la GPU funciona hem dut a terme les següents comprovacions:

- A cada atribut del material li hem assignat un valor força reconeixible, en el nostre cas, ambient = vermell, difus = verd, especular = blau, transparència = groc, i hem fixat shininess = 20.0.
- Després hem fet cinc proves diferents, modificant el fitxer del vertex shader. En les quatre primeres hem assignat la component ambient, difusa, especular i de transparència com a color de l'objecte, i hem obtingut les pantalles següents:
`ambient = (1, 0, 0)`        |  `diffuse = (0, 1, 0)`  
:-------------------------:|:-------------------------:
![ambient](readmeFiles/fase1-pas2/ambient.png)  |  ![diffuse](readmeFiles/fase1-pas2/diffuse.png)
`specular = (0, 0, 1)`        |  `transparency = (1, 1, 0)`  
:-------------------------:|:-------------------------:
![specular](readmeFiles/fase1-pas2/specular.png)  |  ![transparency](readmeFiles/fase1-pas2/transparency.png)

- Per a veure que el float de shininess també es rebia bé a la GPU hem fet que el color de l'objecte vingués donat pel color `color = vec4(0,material.shininess/20.0, material.shininess/20.0, 1);`, és a dir, (0,1,1), i per tant hauriem de veure el color cyan:

![shininess](readmeFiles/fase1-pas2/shininess.png)

- Finalment podem concloure que la informació del material es passa correctament a la GPU.

### Pas 3

### Pas 4

### Pas 5

### Pas 6

*(NOTA2: Breu explicació, si cal, de com replicar els vostres resultats)*

## Additional Information

*(NOTA: Hores de dedicació i problemes que heu tingut fent la pràctica)*
