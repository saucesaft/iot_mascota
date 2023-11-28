# Proyecto IoT

**Módulo Avanzado de Suministro y Control para Optimización Tecnológica de Alimentos**

En la era actual de avances tecnológicos, donde la conectividad y la automatización han transformado diversos aspectos de la vida cotidiana, surge la necesidad de abordar los desafíos asociados con el cuidado de mascotas. Este proyecto se enfoca en el diseño e implementación de un sistema integral y automatizado para la gestión de alimentos, agua y diversión destinado a mascotas. A través de la combinación de tecnologías como sensores, microcontroladores y conectividad a Internet, se busca no solo simplificar la vida de los dueños de mascotas, sino también garantizar el bienestar de los animales de compañía. El informe detalla la metodología utilizada, desde el análisis del problema hasta la construcción del prototipo, destacando técnicas de ingeniería, herramientas empleadas y la infraestructura necesaria. Los resultados presentan aspectos económicos, técnicos y operativos del proyecto, respaldando su viabilidad y relevancia. Se concluye que esta propuesta no solo resuelve problemas prácticos en el cuidado de mascotas, sino que también sienta las bases para futuras innovaciones en el campo de Internet de las cosas aplicado al bienestar animal.

**Un poco de info general**
Nuestro proyecto son 2 NodeMCUs, cada una conectada a sus respectivos sensores y actuadores. La NodeMCU de cambio solo publicara datos al momento de detectar cierto cambio con un threshold indicado en la lectura de los datos, y por otro lado, la NodeMCU intervalo publicara periodicamente cada cierto tiempo a la base de datos.

**Estructura del repo**
- folder `api`: codigo de node.js de la api
- folder `cambio`: codigo arduino/c++ para la nodemcu encargada de los sensores de cambio
- folder `intervalo`: codigo arduino/c++ para la nodemcu encargada de los sensores de intervalo
- `database.sql`: archivo para replicar la base de datos donde se guardarian estos
- `frontend.json`: frontend en formato json para import en [appsmith](https://www.appsmith.com/)
