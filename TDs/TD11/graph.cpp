#include "graph.h"

void Graph::addEdge(unsigned int i, unsigned int j) {
	// Verifier que i et j existent
	if (i>=getNbVertices() || j>=getNbVertices()) // getNbVertices retourne le nombre de sommets 
		throw GraphException("bad argument : a vertex of the edge is not defined");
	// On ajoute l'arc (i,j) : j successeur de i
	adj[i].push_back(j);
	// On incremente le nombre d'arcs
	nbEdges++;
}

void Graph::removeEdge(unsigned int i, unsigned int j) {
	if (i>=getNbVertices() || j>=getNbVertices())
		throw GraphException("bad argument : a vertex of the edge is not defined");
	/** 
	 * Verifier si le sommet j fait bien parti de la liste des successeurs de i
	 * http://www.cplusplus.com/reference/algorithm/find/
	 * InputIterator find (InputIterator first, InputIterator last, const T& val);
	 * Returns an iterator to the first element in the range [first,last) that compares equal to val. If no such element is found, the function returns last.
	 */
	list<unsigned int>::iterator it=find(adj[i].begin(), adj[i].end(), j);
	if (it!=adj[i].end())
	{
		// http://www.cplusplus.com/reference/list/list/erase/
		adj[i].erase(it); // Suppression du sommet j des successeurs de i
		nbEdges--; // Un arc en moins dans le graphe
	}
	else 
		throw GraphException("bad argument : a vertex of the edge is not defined");
}

// Coherent de renvoyer une reference puisqu'il existe une zone memoire contenant la liste des successeurs 
const list<unsigned int> & Graph::getSuccessors(unsigned int i) const {
	if(i>=getNbVertices())
		throw GraphException("bad argument : a vertex of the edge is not defined");
	return adj[i];
}

// Un sommet est predecesseur si l'autre sommet fait parti de ses successeurs
const list<unsigned int> Graph::getPredecessors(unsigned int j) const {
	// i est predecesseur de j si j est successeur de i
	if(j>=getNbVertices())
		throw GraphException("bad argument : a vertex of the edge is not defined");
	list<unsigned int> res; // liste contenant les predecesseurs 
	// Pour chaque sommet i du graphe
	for (unsigned int i = 0; i < adj.size(); i++) {
		// Recherche de j parmis les successeurs de i
		if (find(adj[i].begin(), adj[i].end(), j) != adj[i].end()) {
			// j est successeur de i donc i est predecesseur de j
			res.push_back(i);
		}
	}
	return res;	
}

ostream& operator<<(ostream& f, const Graph& g) {
	f<<"graph "<<g.getName()<<" ("<<g.getNbVertices()<<" vertices and "<<g.getNbEdges()<<" edges)"<<std::endl;
	// Pour chaque sommet
	for(unsigned int i=0; i<g.getNbVertices(); i++) {
		f<<i<<":";
		for(list<unsigned int>::const_iterator it = g.getSuccessors(i).begin(); it != g.getSuccessors(i).end(); it++){
			f<<" "<< *it;
		}
		f<<std::endl;
	}
	return f;
}









































