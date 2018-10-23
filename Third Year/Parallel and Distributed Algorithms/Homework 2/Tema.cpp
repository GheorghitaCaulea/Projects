#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<vector>
#include<queue>
#include<iostream>
#include<algorithm>
#include<fstream>
#include<sstream>
#include<ctime>

using namespace std;

#define TAG_END 3
#define INT_TYPE 1
#define LEAF_TYPE 2

/*Aceasta functie este pentru a construi vectorul de vecini corespunzator fiecarui proces in parte. Primeste ca input
linia corespunzatoare procesului si isi extrage vecinii de pe acea linie.*/
vector<int> getNeigh(string line) {
	string str;
	vector<int> neigh;
	int index = 0, a;
	
	while(line[index] != ':') {
		index ++;
	}

	index ++;
	str = line.substr(index, line.length() - index);
	stringstream s(str);
	
	while(s >> a) {
		neigh.push_back(a);
	}
	
	return neigh;

}
/*Aceasta functie imi returneaza primul integer de pe o linie.*/
int getFirst(string line) {
	int a;
	stringstream s(line);
	s >> a;
	
	return a;
}

/*Aceasta functie determina filtrul ce urmeaza a fi aplicat unei imagini.*/
int getFiltre(string line) {
	string subs;
	stringstream s(line);
	s >> subs;
	
	if(subs.compare("sobel") == 0)
		return 1;
	else 
		return 2;
}

/*Aceasta functie imi returneaza numele imagii ce urmeaza a fi procesata. Primeste ca input o linie de forma celor din 'imagini.in'.*/
string getImageName(string line) {
	string subs;
	stringstream s(line);
	s >> subs;
	s >> subs;
	return subs;
}

/*Aceasta functie imi returneaza numele imagiide output. Primeste ca input o linie de forma celor din 'imagini.in'.*/
string getOutputImageName(string line) {
	string subs;
	stringstream s(line);
	s >> subs;
	s >> subs;
	s >> subs;
	return subs;
}

/*Aceasta functie realizeaza aproximarea pixelilor(pentru pixelii care depasesc valoarea maxima sau minima) in limita lor(0-255).*/
int my_aprox(int n) {
	if(n > 255)
		return 255;
	else if(n < 0)
		return 0;
	else
	 	return n;
}

/*Aceasta functie aplica filtru dat ca parametru pe un bloc dintr-o imagine(1 - sobel, 2 - mean_removal).*/
int * apply_filtre(int m_aux[], int width, int height, int filt) {

	int * v, **m, **fin_m, i, j;
	v = new int[height * width];
	m = new int*[height];
	fin_m = new int*[height];
	
	for(i = 0; i < height; i ++){
		m[i] = new int[width];
		fin_m[i] = new int[width];
	}

	for(i = 0; i < height; i ++) {
		for(j = 0; j < width; j++) {
			m[i][j] = m_aux[(i * width) + j];
		}
	}
	if(filt == 1) {
		for(i = 1; i < (height - 1); i ++) {
			for(j = 0; j < width; j++) {
				if(j == 0) {
					fin_m[i][j] = my_aprox((-1) * m[i - 1][j + 1] + (-2) * m[i][j + 1] + (-1) * m[i + 1][j + 1] + 127);
				} else if (j == width - 1) {
					fin_m[i][j] = my_aprox(1 * m[i - 1][j - 1] + 2 * m[i][j - 1] + 1 * m[i + 1][j - 1] + 127);
				} else {
					fin_m[i][j] = my_aprox((-1) * m[i - 1][j + 1] + (-2) * m[i][j + 1] + (-1) * m[i + 1][j + 1] + 
											1 * m[i - 1][j - 1] + 2 * m[i][j - 1] + 1 * m[i + 1][j - 1] + 127);
				}
			}
		}	
	} else {
		for(i = 1; i < (height - 1); i ++) {
			for(j = 0; j < width; j++) {
				if(j == 0) {
					fin_m[i][j] = my_aprox((-1) * m[i - 1][j + 1] + (-1) * m[i][j + 1] + (-1) * m[i + 1][j + 1] +
											(-1) * m[i - 1][j] + (9) * m[i][j] + (-1) * m[i + 1][j]);
				} else if (j == width - 1) {
					fin_m[i][j] = my_aprox((-1) * m[i - 1][j - 1] + (-1) * m[i][j - 1] + (-1) * m[i + 1][j - 1] +
											(-1) * m[i - 1][j] + (9) * m[i][j] + (-1) * m[i + 1][j]);
				} else {
					fin_m[i][j] = my_aprox((-1) * m[i - 1][j + 1] + (-1) * m[i][j + 1] + (-1) * m[i + 1][j + 1] +
											(-1) * m[i - 1][j] + (9) * m[i][j] + (-1) * m[i + 1][j] +
											(-1) * m[i - 1][j - 1] + (-1) * m[i][j - 1] + (-1) * m[i + 1][j - 1]);
				}
			}
		}
	}
	for(i = 0; i < height; i ++) {
		for(j = 0; j < width; j++) {
			v[i * width + j] = fin_m[i][j];
		}
	}

	for(i = 0; i < height; i ++){
		delete [] m[i];
		delete [] fin_m[i];
	}

	delete [] m;
	delete [] fin_m;

	return v;
}

int main(int argc, char * argv[]) {
	int rank, nProc, i, a, NF, k, cont = 0, work = 0;
	string line;

	MPI_Init(&argc, &argv);
	
	MPI_Status status;
	MPI_Request request;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nProc);

	
	ifstream img1 (argv[2]);

	/*Determin parametrul NF(numarul de imagini de prelucrat).*/
	getline(img1, line);
	NF = getFirst(line);
	img1.close();

	/*Voi procesa toate imaginile din fisierul de intrare.*/
	for(k = 0; k < NF; k ++) {
		
		if(rank == 0) {
			/*Deschid fisierele pentru a extrage informatiile ce urmeaza a fi procesate.*/
			ifstream top (argv[1]);
			ifstream img (argv[2]);
			int width, height, a, index = 0, start = 0, *aux_pixels, cont, no_line = 0, tag;
			string img_name, out_img_name;
			vector<int>  children;
			
			/*Citesc linia din topologie corespunzatoare nodului cu rank-ul 0.*/
			for(i = 0; i <= rank; i ++){
				getline(top, line);
			}
			/*Construiesc vectorul de copii folosindu-ma de functia 'getNeigh'.*/
			children = getNeigh(line);
			
			/*Identific ce filtru urmeaza sa fie aplicat.*/
			for(i = 0; i < k + 2; i ++) {
				getline(img, line);
			}

			tag = getFiltre(line);

			/*Construiesc numele imaginii de input si respectiv output.*/
			img_name = getImageName(line);
			out_img_name = getOutputImageName(line);

			/*Deschid imaginea data ca input pentru citirea pixelilor.*/
			ifstream photo (img_name.c_str());
			
			getline(photo, line);
			no_line ++;
			stringstream s(line);
			string buf;
			char sep;
			int sw = 0;
			
			/*Voi parcurge header-ul imaginii si voi retine din cate linii este acesta construit, iar mai apoi voi citi fiecare pixel,
			retinand ce separator se afla intre acestia.*/
			s >> buf;
			if(s >> a) {
				width = a;
				cont = a;
				if(s >> a) {
					height = a;
					aux_pixels = new int[(height + 2) * width];
					for(i = 0; i < width; i ++)
						aux_pixels[i] = 0;
					if(s >> a) {
						while (s >> a) {
							aux_pixels[cont] = a;
							cont ++;
							if(sw == 0) {
								s >> sep;
								sw = 1;
								if(sep == '\0')
									sep = '\n';
							}
						}
					} else {
						getline(photo, line);
						no_line ++;
						stringstream s1(line);
						s1 >> buf;
						while(buf.compare("#") == 0) {
							getline(photo, line);
							no_line ++;
							stringstream s2(line);
							s2 >> buf;
						}
						stringstream s3(line);
						s3 >> a;
						while (s3 >> a) {
							aux_pixels[cont] = a;
							cont ++;
							if(sw == 0) {
								s3 >> sep;
								sw = 1;
								if(sep == '\0')
									sep = '\n';
							}
						}	
					}
				} else {
					getline(photo, line);
					no_line ++;
					stringstream s4(line);
					s4 >> buf;
					while(buf.compare("#") == 0) {
						getline(photo, line);
						no_line ++;
						stringstream s5(line);
						s5 >> buf;
					}
					stringstream s6(line);
					s6 >> a;
					height = a;
					aux_pixels = new int[(height + 2) * width];
					for(i = 0; i < width; i ++)
						aux_pixels[i] = 0;
					if(s6 >> a) {
						while (s6 >> a) {
							aux_pixels[cont] = a;
							cont ++;
							if(sw == 0) {
								s6 >> sep;
								sw = 1;
								if(sep == '\0')
									sep = '\n';
							}
						}	
					} else {
						getline(photo, line);
						no_line ++;
						stringstream s1(line);
						s1 >> buf;
						while(buf.compare("#") == 0) {
							getline(photo, line);
							no_line ++;
							stringstream s2(line);
							s2 >> buf;
						}
						stringstream s3(line);
						s3 >> a;
						while (s3 >> a) {
							aux_pixels[cont] = a;
							cont ++;
							if(sw == 0) {
								s3 >> sep;
								sw = 1;
								if(sep == '\0')
									sep = '\n';
							}
						}	
					}
				}
			} else {
				getline(photo, line);
				no_line ++;
				stringstream s7(line);
				s7 >> buf;
				while(buf.compare("#") == 0) {
					getline(photo, line);
					no_line ++;
					stringstream s8(line);
					s8 >> buf;
				}

				stringstream s9(line);
				s9 >> a;
				width = a;
				cont  = a;

				if(s9 >> a) {
					height = a;
					aux_pixels = new int[(height + 2) * width];
					
					for(i = 0; i < width; i ++)
						aux_pixels[i] = 0;

					if(s9 >> a) {
						while (s9 >> a) {
							aux_pixels[cont] = a;
							cont ++;
							if(sw == 0) {
								s9 >> sep;
								sw = 1;
								if(sep == '\0')
									sep = '\n';
							}
						}	

					} else {
						getline(photo, line);
						no_line ++;
						stringstream s1(line);
						s1 >> buf;
						
						while(buf.compare("#") == 0) {
							getline(photo, line);
							no_line ++;
							stringstream s2(line);
							s2 >> buf;
						}
						stringstream s3(line);
						s3 >> a;
						while (s3 >> a) {
							aux_pixels[cont] = a;
							cont ++;
							if(sw == 0) {
								s3 >> sep;
								sw = 1;
								if(sep == '\0')
									sep = '\n';
							}
						}	
					}
				} else {
					getline(photo, line);
					no_line ++;
					stringstream s4(line);
					s4 >> buf;
					while(buf.compare("#") == 0) {
						getline(photo, line);
						no_line ++;
						stringstream s5(line);
						s5 >> buf;
					}
					stringstream s6(line);
					s6 >> a;
					height = a;
					aux_pixels = new int[(height + 2) * width];
					
					for(i = 0; i < width; i ++)
						aux_pixels[i] = 0;

					if(s6 >> a) {
						while (s6 >> a) {
							aux_pixels[cont] = a;
							cont ++;
							if(sw == 0) {
								s6 >> sep;
								sw = 1;
								if(sep == '\0')
									sep = '\n';
							}
						}	
					} else {
						getline(photo, line);
						no_line ++;
						stringstream s1(line);
						s1 >> buf;
						while(buf.compare("#") == 0) {
							getline(photo, line);
							no_line ++;
							stringstream s2(line);
							s2 >> buf;
						}
						stringstream s3(line);
						s3 >> a;
						while (s3 >> a) {
							aux_pixels[cont] = a;
							cont ++;
							if(sw == 0) {
								s3 >> sep;
								sw = 1;
								if(sep == '\0')
									sep = '\n';
							}
						}	
					}
				}
			} 

			while(getline(photo, line)) {
				stringstream str(line);
				while(str >> a) {
					aux_pixels[cont] = a;
					cont ++;
					if(sw == 0) {
						str >> sep;
						sw = 1;
						if(sep == '\0')
							sep = '\n';
					}
				}	
			}

			/*Dupa ce am determinat cate linii contine imaginea, imi creez chunk-uri in functie de numarul de copii.*/
			int aux = height, j, ind = 0;
			int chunk = height / children.size();

			for(j = 0; j < width; j ++) {
				aux_pixels[cont] = 0;
				cont ++;
			}

			int new_chunck = chunk;
			new_chunck += 2;
			/*Pentru fiecare copil voi efectua urmatoarele.*/
			for(i = 0; i < children.size(); i ++) {
				/*Trimit fiecarul copil latimea fiecarei imagini pe canalul corespunzator filtrului ce urmeaza a fi aplicat.*/
				MPI_Send(&width, 1, MPI_INT, children[i], tag, MPI_COMM_WORLD);
				if(height >= children.size()) {
					/*Pentru ultimul copil voi trimite numarul liniilor ramase.*/
					if(i == children.size() - 1) {	
						MPI_Send(&aux, 1, MPI_INT, children[i], tag, MPI_COMM_WORLD);
						int * v, it = 0;
						v = new int[(aux + 2) * width];
						for(j = ind; j < cont; j ++){
							v[it] = aux_pixels[j];
							it++;
						}
						MPI_Send(v, ((aux + 2) * width), MPI_INT, children[i], tag, MPI_COMM_WORLD);
						delete [] v;
					/*Pentru toti copii pana la ultimul voi trimite atatea linii cate am calculat ca are un chunck.*/	
					} else {
						MPI_Send(&chunk, 1, MPI_INT, children[i], tag, MPI_COMM_WORLD);
						aux -= chunk;
						int * v, it = 0;
						v = new int[new_chunck * width];
						for(j = ind; j < (ind + (new_chunck * width)); j ++){
							v[it] = aux_pixels[j];
							it++;
						}
						ind += (new_chunck - 2)* width;
						MPI_Send(v, (new_chunck * width), MPI_INT, children[i], tag, MPI_COMM_WORLD);
						delete [] v;
					}
				} else {
					cout << "Nu indeplinesc conditia de trimitere!" << endl;
				}	
			}

			delete [] aux_pixels;
			 /*Astept primirea liniilor modificate si construiesc noua matrice de pixeli. Tratez special ultimul copil pentru ca de la
			 el astept un numar diferit de linii.*/
			int *m_trans;
			m_trans = new int[height * width]; 
			int index1 = 0, u;
			for(i = 0; i < children.size() - 1; i++) {
				int * m_chunck;
				m_chunck = new int[width * chunk];
				MPI_Recv(m_chunck, (chunk * width), MPI_INT, children[i], tag, MPI_COMM_WORLD, &status);
				for(u = 0; u < (chunk * width); u ++) {
					m_trans[index1] = m_chunck[u];
					index1 ++;
				}
				delete [] m_chunck;
			}

			int * m_chunck;
			m_chunck = new int[width * aux]; 
			MPI_Recv(m_chunck, (aux * width), MPI_INT, children[i], tag, MPI_COMM_WORLD, &status);
			for(u = 0; u < (aux * width); u ++) {
				m_trans[index1] = m_chunck[u];
				index1 ++;
			}
			delete [] m_chunck;
			photo.close();

			/*Scriu vechiul header si noii pexeli in imaginea ce urmeaza a fi intoarsa ca output.*/
			ifstream again_photo (img_name.c_str());
			ofstream new_photo (out_img_name.c_str());
			for(i = 0; i < no_line; i ++) {
				getline(again_photo, line);
				new_photo << line;
				new_photo << "\n";
			}

			for(i = 0; i < (width * height); i ++) {
				new_photo << m_trans[i];
				new_photo << sep;
			}
			delete [] m_trans;
			again_photo.close();
			new_photo.close();
			top.close();
			img.close();

			/*Daca am ajuns la final astept primirea vectorului ce reprezinta elemntul de statistica. In acest vector elementele consecutive
			sunt perechi de forma (nr_proc, nr_linii_proc). Adaug acestui vector numarul de linii procesate de radacina(0) si apoi ordonez 
			vectorul dupa indicele procesului, ca la sfarsit sa il scriu in fisierul de statistica.*/
			if(k == NF - 1) {
				vector<int> vf;
				int tot = 0;
				for (i = 0; i < children.size(); i ++) {
					int cant;
					MPI_Recv(&cant, 1, MPI_INT, children[i], TAG_END, MPI_COMM_WORLD, &status);
					tot += cant;
					int *v_rec;
					v_rec = new int[cant];
					MPI_Recv(v_rec, cant, MPI_INT, children[i], TAG_END, MPI_COMM_WORLD, &status);
					for(int y = 0; y < cant; y ++) {
						vf.push_back(v_rec[y]);
					}
				}
				vf.push_back(0);
				vf.push_back(0);
				int *ord;
				ord = new int[vf.size()/2];
				for(i = 0; i < vf.size(); i += 2) {
					ord[vf[i]] = vf[i + 1];

				}
				ofstream st (argv[3]);

				for(i = 0; i < vf.size() / 2; i ++) {
					st << i;
					st << ": ";
					st << ord[i];
					st << "\n";
				}
				delete [] ord;
				st.close();
			}
				
		} else {
			
			ifstream top (argv[1]);
			int height, width, ind = 0, j, last, parent, tag;
			vector<int> children;
			
			/*Voi construi vectorul de copii corespunzator procesului(acest vector contine si parintele).*/
			for(i = 0; i <= rank; i ++){
				getline(top, line);
			}
			
			children = getNeigh(line);
			/*Pentru fiecare proces intermediar(nu e nici radacina nici frunza) voi face urmatoarele.*/
			if(children.size() != 1) {
				/*Astept primirea latimii imaginii de procesat. Prin acest prim mesaj descopar si parintele dar si filtrul ce 
				urmeaza a fi aplicat.*/
				MPI_Recv(&width, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
				
				if(status.MPI_TAG == 1) {
					tag = 1;
				} else {
					tag = 2;
				}
				parent = status.MPI_SOURCE;

				/*Pentru fiecare proces determin care este ultimul copil. Este importanta atunci cand trimit ultimul bloc de linii.*/
				for(i = 0; i < children.size(); i ++) {
					if(children[i] != parent)
						last = children[i];
				}

				/*Trimit mai departe latimea imaginii pe tag-ul corespunzator filtrului ce urmeaza a fi aplicat.*/
				for(i = 0; i < children.size(); i ++) {
					if(children[i] != parent)
						MPI_Send(&width, 1, MPI_INT, children[i], tag, MPI_COMM_WORLD);
				}

				/*Astept primirea inaltimii blocului de procesat.*/
				MPI_Recv(&height, 1, MPI_INT, parent, tag, MPI_COMM_WORLD, &status);
				int aux = height;
				int chunk = height / (children.size() - 1);
				
				/*Calculez si transmit mai departe inaltimea noilor blocuri de procesat.*/
				for(i = 0; i < children.size(); i ++) {
					if(children[i] != parent) {
						if(children[i] == last) {	
							MPI_Send(&aux, 1, MPI_INT, children[i], tag, MPI_COMM_WORLD);
						} else {
							MPI_Send(&chunk, 1, MPI_INT, children[i], tag, MPI_COMM_WORLD);
							aux -= chunk;
						}
					}
				}

				/*Astept primirea blocului de procesat dupa care il voi imparti si transmite mai departe catre copii.*/
				int *m;
				m = new int[(height + 2) * width];
				int new_chunck = chunk;
				new_chunck += 2;
				MPI_Recv(m, ((height + 2) * width), MPI_INT, parent, tag, MPI_COMM_WORLD, &status);
				for(i = 0; i < children.size(); i ++) {
					if(height >= (children.size() - 1)) {
						if(children[i] != parent) {
							if(children[i] == last) {	
								
								int *v, it = 0;
								v = new int[(aux + 2) * width];
								for(j = ind; j < (height + 2) * width; j ++){
									v[it] = m[j];
									it++;
								}
								MPI_Send(v, ((aux + 2) * width), MPI_INT, children[i], tag, MPI_COMM_WORLD);
								delete [] v;
							} else {

								int *v, it = 0;
								v = new int[new_chunck * width];
								for(j = ind; j < (ind + (new_chunck * width)); j ++){
									v[it] = m[j];
									it++;
								}
								ind += (new_chunck - 2)* width;
								MPI_Send(v, (new_chunck * width), MPI_INT, children[i], tag, MPI_COMM_WORLD);
								delete [] v;
							}
						}
					}		
				}
				delete [] m;
				
				/*Aceasta parte este pentru a primi si trimite mai departe matricea de pixeli dupa aplicarea filtrului.*/
				int * m_trans;
				m_trans = new  int[height * width];
				int index = 0, u;
				for(i = 0; i < children.size(); i++) {
					if(children[i] != parent) {
						if(children[i] == last){
							int *m_chunck;
							m_chunck = new int[width * aux];
							MPI_Recv(m_chunck, (aux * width), MPI_INT, children[i], tag, MPI_COMM_WORLD, &status);
							for(u = 0; u < (aux * width); u ++) {
								m_trans[index] = m_chunck[u];
								index ++;
							}
							delete [] m_chunck;
						} else {
							int *m_chunck;
							m_chunck = new int[width * chunk];
							MPI_Recv(m_chunck, (chunk * width), MPI_INT, children[i], tag, MPI_COMM_WORLD, &status);
							for(u = 0; u < (chunk * width); u ++) {
								m_trans[index] = m_chunck[u];
								index ++;
							}
							delete [] m_chunck;
						}		
					}	
				}

				MPI_Send(m_trans, (height * width), MPI_INT, parent, tag, MPI_COMM_WORLD);
				delete [] m_trans;
				top.close();

				/*Daca am ajuns la finalul procesarii, astept primirea vectorului ce reprezinta elemntul de statistica
				la care adaug elementele pentru procesul curent, dupa care voi trimite mai departe vectorul de statistica, catre
				nodul parinte.*/
				if(k == NF - 1) {
					vector<int> vf;
					int tot = 0;
					for (i = 0; i < children.size(); i ++) {
						if(children[i] != parent) {
							int cant;
							MPI_Recv(&cant, 1, MPI_INT, children[i], TAG_END, MPI_COMM_WORLD, &status);
							tot += cant;
							int *v_rec;
							v_rec = new int[cant];
							MPI_Recv(v_rec, cant, MPI_INT, children[i], TAG_END, MPI_COMM_WORLD, &status);
							for(int y = 0; y < cant; y ++) {
								vf.push_back(v_rec[y]);
							}
						}	
					}
					vf.push_back(rank);
					vf.push_back(0);
					tot += 2;
					int *v_send;
					v_send = new int[tot];
					for(int y = 0; y < tot; y ++) {
						v_send[y] = vf[y];
					}
					MPI_Send(&tot, 1, MPI_INT, parent, TAG_END, MPI_COMM_WORLD);
					MPI_Send(v_send, tot, MPI_INT, parent, TAG_END, MPI_COMM_WORLD);
					delete []  v_send;
				}
				
			} else {
				/*Pentru fiecare nod frunza voi efectua urmatoarele.*/
				int parent, type, filt;
				/*Astept primirea latimii imaginii. Prin acest prim mesaj determin parintele procesului dar si filtrul
				ce urmeaza a fi aplicat.*/
				MPI_Recv(&width, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

				if(status.MPI_TAG == 1) {
					tag = 1;
					filt = 1;
				} else {
					tag = 2;
					filt = 2;
				}

				parent = status.MPI_SOURCE;
				type = LEAF_TYPE;
				/*Primesc inaltimea imaginii.*/
				MPI_Recv(&height, 1, MPI_INT, parent, tag, MPI_COMM_WORLD, &status);
				work += height;
				int * m;
				m = new int[(height + 2) * width];
				/*Primesc blocul de procesat.*/
				MPI_Recv(m, ((height + 2) * width), MPI_INT, parent, tag, MPI_COMM_WORLD, &status);

				int * m1;
				m1 = new int[height * width];
				int index = 0;
				int * trans_m;
				/*Aplic filstrul corespunzator canalului pe care s-au transmis mesajele.*/
				trans_m = apply_filtre(m, width, (height + 2), filt);

				for(j = 1; j  <= height; j ++) {
					for(i = 0; i < width; i ++) {
						m1[index] = trans_m[(j * width) + i];
						index ++;
					}
				}	
				/*Trimit catre parinte blocul procesat.*/
				MPI_Send(m1, (height * width), MPI_INT, parent, tag, MPI_COMM_WORLD);
				delete [] m;
				delete [] m1;
				delete [] trans_m;	
				/*Daca am ajuns la finalul procesarii trimit datele ce tin de statistica.*/
				if(k == NF - 1) {
					int nr = 2, *stat;
					MPI_Send(&nr, 1, MPI_INT, parent, TAG_END, MPI_COMM_WORLD);
					stat = new int[2];
					stat[0] = rank;
					stat[1] = work;
					MPI_Send(stat, 2, MPI_INT, parent, TAG_END, MPI_COMM_WORLD);
					delete [] stat;
				}
			}
		}
	}
	
	MPI_Finalize();
	return 0;
}