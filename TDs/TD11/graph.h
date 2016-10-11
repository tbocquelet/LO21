#if !defined(_GRAPH_H)
#define _GRAPH_H

#include <string>
#include <stdexcept>
#include <iostream>
// Librairies pour utiliser nos conteneurs 
#include <algorithm>
#include <vector>
#include <list>
#include <map>
#include <set>

using namespace std;

class GraphException : public exception {
	string info; 
public:
	GraphException(const string& i) throw(): info(i) {} 
	virtual ~GraphException() throw(){}
	const char* what() const throw() { return info.c_str(); }
};

// On suppose qu'on travaille avec un multigraphe et donc que plusieurs arcs peuvent relier un meme sommet
// Verifier si un element est ou non dans une liste : methode find() --> header <algorithm>

class Graph { 
	// vector : pour acceder rapidement au i eme element
	// liste : pour insertion/suppression rapide
	vector<list<unsigned int> > adj;  // liste d'adjacence
	string name; // nom du graphe
	unsigned int nbEdges; // nombre d'arcs : simplifie l'implementation de getNbEdges
public:
	// Constructeur avec nom du graphe et le nombre de sommets
	// On cree un vecteur et a chaque emplacement de ce vecteur va etre attribue une liste vide
	Graph(const string& n, unsigned int nb): name(n), nbEdges(0), adj(nb) {}
	const string& getName() const { return name; }
	// Notre vecteur contient autant de cases qu'il y a de sommets
	unsigned int getNbVertices() const { return adj.size(); }
	unsigned int getNbEdges() const { return nbEdges; }
	void addEdge(unsigned int i, unsigned int j);
	void removeEdge(unsigned int i, unsigned int j);
	const list<unsigned int>& getSuccessors(unsigned int i) const; 
	const list<unsigned int> getPredecessors(unsigned int j) const;
};

ostream& operator<<(ostream& f, const Graph& g);

// Un element apparait au plus une fois dans un set(pas de multigraphe).
// Implementer une methode de comparaison de deux elements pour la classe set --> contrepartie de l'utilisation de la classe
// http://www.cplusplus.com/reference/set/set/
// http://www.cplusplus.com/reference/map/map/
// Map : conteneur associatif permettant de stocker des ensembles [cle]=valeur ici cle = sommet, valeur associee = liste de successeur

template<class Vertex> class GraphG {
	map<Vertex,set<Vertex> > adj;
	string name; 
	unsigned int nbEdges;
public:
	GraphG(const string& n) : name(n), nbEdges(0) {} // pas besoin de constructeur pour adj, le constructeur par defaut construit un conteneur vide de base
 	const string& getName() const { return name; }
	unsigned int getNbVertices() const { return adj.size(); }
	unsigned int getNbEdges() const { return nbEdges; }
	void addVertex(const Vertex& i);
	void addEdge(const Vertex& i, const Vertex& j); 
	void removeEdge(const Vertex& i, const Vertex& j); 
	void removeVertex(const Vertex& i);
	void print(ostream& f) const;
};

// Ajoute le sommet i si celui-ci n'existe pas
// Ne fais rien si ce sommet existe deja
template<class Vertex>
void GraphG<Vertex>::addVertex(const Vertex& i) {
	// Informe le compilateur que le nom dependant de Vertex "iterator" est un type
	// Facultatif, syntaxe lourde :
	//typename map<Vertex, set<Vertex> >::iterator it=adj[i].find(i);
	// if(it == adj.end()) {
	// 	adj[i]=set<Vertex>();
	// }
	adj[i]; // si l'element existe deja, une reference est renvoyee, si l'element n'existe pas, l'element est insere
}

// Ajout d'un arc entre deux sommets
// Creation de ces sommets si ils n'existent pas
template<class Vertex>
void GraphG<Vertex>::addEdge(const Vertex& i, const Vertex& j) {
	addVertex(i); // on pourrait la supprimer car adj[i] du if en dessous realise l'operation
	addVertex(j);
	// http://www.cplusplus.com/reference/map/map/insert/
	if(adj[i].insert(j).second) {
		nbEdges++;
	}
}

// Supprime un arc si celui-ci existe
// Ne fait rien sinon
template<class Vertex>
void GraphG<Vertex>::removeEdge(const Vertex& i, const Vertex& j) {
	// Verifier si i existe bien
	typename map<Vertex, set<Vertex> >::iterator it=adj.find(i);
	if(it!=adj.end()) { // Le sommet i existe
		// http://www.cplusplus.com/reference/set/set/erase/
		// Suppression de j si celui-ci fait parti des successeurs
		if(adj[i].erase(j)) { // Renvoie le nombre d'elements supprimes
			nbEdges--;
		}
	}
}

// Supprime un sommet et tous les arcs referencant ce sommet
// Ne fais rien si le sommet n'existe pas
template<class Vertex>
void GraphG<Vertex>::removeVertex(const Vertex& i) {
	if (adj.erase(i)) { // Si le sommet a ete supprime
		// Pour chaque sommet existant
		for(typename map<Vertex, set<Vertex> >::iterator it=adj.begin(); it!=adj.end(); it++) {
			removeEdge(it->first, i); // Supprime l'arc si il existe, ne fait rien sinon
			// On peut faire ca uniquement parcequ'on ne fait rien dans removeEdge lorsque l'arc n'existe pas
		}
	}
}

template<class Vertex>
void GraphG<Vertex>::print(ostream& f) const {
	f << "graph "<<getName()<<" ("<<getNbVertices()<<"vertices and "<<getNbEdges()<<" edges)"<<endl;
	// Pour chaque sommet
	for(typename map<Vertex, set<Vertex> >::const_iterator it=adj.begin(); it!=adj.end(); it++) {
		// Affichage du sommet 
		f<<it->first<<":"; // On suppose que l'operateur d'insertion a ete defini pour un objet de type Vertex
		for(typename set<Vertex>::const_iterator it2=it->second.begin(); it2!=it->second.end(); it2++){
			f<<" "<< *it2;
		}
		f<<endl;
	}
}

template<class Vertex> 
ostream& operator<<(ostream& f, const GraphG<Vertex>& g) {
	g.print(f);
	return f;
}

#endif















