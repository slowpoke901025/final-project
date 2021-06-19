struct MAP
{
	int main[55][100];
	int vice[55][100];
	int treasure[55][100];
};
extern struct MAP Map;

void setMap(int[][100],int[][100],int);
void resetMap();
