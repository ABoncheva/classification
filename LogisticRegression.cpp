#include <iostream>
#include <vector>
#include <array>
#include <cmath>
#include <random>


using namespace std;

constexpr unsigned char weights_num = 3;
constexpr unsigned char features_num = 2;

using features = array<double, features_num>;

struct example
{
	features x;
	bool y;
};

static vector<example> trainingSet =
{
	{{34.62365962,78.02469282},0},
	{{30.28671077,43.89499752},0},
	{{35.84740877,72.90219803},0},
	{{60.18259939,86.3085521 },1},
	{{79.03273605,75.34437644},1},
	{{45.08327748,56.31637178},0},
	{{61.10666454,96.51142588},1},
	{{75.02474557,46.55401354},1},
	{{76.0987867, 87.42056972},1},
	{{84.43281996,43.53339331},1},
	{{95.86155507,38.22527806},0},
	{{75.01365839,30.60326323},0},
	{{82.30705337,76.4819633 },1},
	{{69.36458876,97.71869196},1},
	{{39.53833914,76.03681085},0},
	{{53.97105215,89.20735014},1},
	{{69.07014406,52.74046973},1},
	{{67.94685548,46.67857411},0},
	{{70.66150955,92.92713789},1},
	{{76.97878373,47.57596365},1},
	{{67.37202755,42.83843832},0},
	{{89.67677575,65.79936593},1},
	{{50.53478829,48.85581153},0},
	{{34.21206098,44.2095286 },0},
	{{77.92409145,68.97235999},1},
	{{62.27101367,69.95445795},1},
	{{80.19018075,44.82162893},1},
	{{93.1143888, 38.80067034},0},
	{{61.83020602,50.25610789},0},
	{{38.7858038, 64.99568096},0},
	{{61.37928945,72.80788731},1},
	{{85.40451939,57.05198398},1},
	{{52.10797973,63.12762377},0},
	{{52.04540477,69.43286012},1},
	{{40.23689374,71.16774802},0},
	{{54.63510555,52.21388588},0},
	{{33.91550011,98.86943574},0},
	{{64.17698887,80.90806059},1},
	{{74.78925296,41.57341523},0},
	{{34.18364003,75.23772034},0},
	{{83.90239366,56.30804622},1},
	{{51.54772027,46.85629026},0},
	{{94.44336777,65.56892161},1},
	{{82.36875376,40.61825516},0},
	{{51.04775177,45.82270146},0},
	{{62.22267576,52.06099195},0},
	{{77.19303493,70.4582    },1},
	{{97.77159928,86.72782233},1},
	{{62.0730638, 96.76882412},1},
	{{91.5649745, 88.69629255},1},
	{{79.94481794,74.16311935},1},
	{{99.27252693,60.999031  },1},
	{{90.54671411,43.39060181},1},
	{{34.52451385,60.39634246},0},
	{{50.28649612,49.80453881},0},
	{{49.58667722,59.80895099},0},
	{{97.64563396,68.86157272},1},
	{{32.57720017,95.59854761},0},
	{{74.24869137,69.82457123},1},
	{{71.79646206,78.45356225},1},
	{{75.39561147,85.75993667},1},
	{{35.28611282,47.02051395},0},
	{{56.2538175, 39.26147251},0},
	{{30.05882245,49.59297387},0},
	{{44.66826172,66.45008615},0},
	{{66.56089447,41.09209808},0},
	{{40.45755098,97.53518549},1},
	{{49.07256322,51.88321182},0},
	{{80.27957401,92.11606081},1},
	{{66.74671857,60.99139403},1},
	{{32.72283304,43.30717306},0},
	{{64.03932042,78.03168802},1},
	{{72.34649423,96.22759297},1},
	{{60.45788574,73.0949981 },1},
	{{58.84095622,75.85844831},1},
	{{99.8278578, 72.36925193},1},
	{{47.26426911,88.475865  },1},
	{{50.4581598, 75.80985953},1},
	{{60.45555629,42.50840944},0},
	{{82.22666158,42.71987854},0},
	{{88.91389642,69.8037889 },1},
	{{94.83450672,45.6943068 },1},
	{{67.31925747,66.58935318},1},
	{{57.23870632,59.51428198},1},
	{{80.366756,  90.9601479 },1},
	{{68.46852179,85.5943071 },1},
	{{42.07545454,78.844786  },0},
	{{75.47770201,90.424539  },1},
	{{78.63542435,96.64742717},1},
	{{52.34800399,60.76950526},0},
	{{94.09433113,77.15910509},1},
	{{90.44855097,87.50879176},1},
	{{55.48216114,35.57070347},0},
	{{74.49269242,84.84513685},1},
	{{89.84580671,45.35828361},1},
	{{83.48916274,48.3802858 },1},
	{{42.26170081,87.10385094},1},
	{{99.31500881,68.77540947},1},
	{{55.34001756,64.93193801},1},
	{{74.775893,   89.5298129},1}
};

static vector<features> testSet;
static double w[weights_num];

double sigmoid(double z)
{
	return 1.0 / (1.0 + expl(-z));
}

double predict(const features& x)
{
	double z = w[0] + w[1] * x[0] + w[2] * x[1];

	return sigmoid(z);
}

double cost()
{
	double j = 0;
	for (auto& e : trainingSet)
	{
		double p = predict(e.x);
		j += e.y * logl(p) + (1 - e.y) * logl(1 - p);
	}
	return -j / trainingSet.size();
}


int main()
{
	//cost function derivatives
	double dJdw0 = 0, dJdw1 = 0, dJdw2 = 0;

	//learning rate
	double alpha = 0.002;

	ios::sync_with_stdio(false);
	for (int i = 0; i < 2000000; i++)
		//do
	{
		if (i % 100000 == 0)
		{
			cout << "W0: " << w[0] << " W1: " << w[1] << " W2: " << w[2] << "  Cost: " << cost() << " Iterations: " << i << "/2000000\n";
		}

		dJdw0 = 0;
		dJdw1 = 0;
		dJdw2 = 0;

		//calculate cost function derivatives
		for (auto e : trainingSet)
		{
			double p = predict(e.x);
			dJdw0 += (p - e.y);
			dJdw1 += (p - e.y) * e.x[0];
			dJdw2 += (p - e.y) * e.x[1];
		}

		//take mean, apply learning rate and adjust weights
		w[0] = w[0] - alpha * (dJdw0 / trainingSet.size());
		w[1] = w[1] - alpha * (dJdw1 / trainingSet.size());
		w[2] = w[2] - alpha * (dJdw2 / trainingSet.size());

	}

	cout << "W0: " << w[0] << " W1: " << w[1] << " W2: " << w[2] << "  Cost: " << cost() << " Iterations: 2000000/2000000\n";

	cout << "\n\nRandom Generated Test Cases\n";

	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(0.0, 100.0);

	for (int n = 0; n < 20; ++n) {

		testSet.push_back({ dis(gen), dis(gen) });
	}

	for (auto f : testSet)
	{
		cout << "Exam 1: " << f[0] << " Exam 2: " << f[1] << " Admission: " << (predict(f) >= 0.5 ? 1 : 0) << '\n';
	}

	features userTest;

	cout << "\nEnter space separated results from the two exams to get admission prediction:\n";

	while (cin >> userTest[0] >> userTest[1])
	{
		cout << "Exam 1: " << userTest[0] << " Exam 2: " << userTest[1] << " Admission: " << (predict(userTest) >= 0.5 ? 1 : 0) << '\n';
	}

	return 0;
}