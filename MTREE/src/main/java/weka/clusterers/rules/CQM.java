package weka.clusterers;

import weka.core.DistanceFunction;
import weka.core.EuclideanDistance;
import weka.core.Instance;
import weka.core.Instances;

/**
 * Computes different metrics for testing the quality
 * of clusters generated by SimpleKMeans algorithm.
 * Uses the Euclidean distance.
 */
public class CQM
{
	/** Holds how many decimals the metrics should have */
	protected int nrDecimals = 2;	
	
	/**
	 * Set the number of decimals
	 * 
	 * @param nrDecimals the number of decimals
	 */
	public void setNrDecimals(int nrDecimals)
	{
		this.nrDecimals = nrDecimals;
	}
	
	/**
	 * Removes decimals from a given number
	 * 
	 * @param number which decimals should be removed
	 * @return number with the correct number of decimals 
	 */
	public double removeDecimals(double number)
	{
		number = ((int)(number * Math.pow(10, nrDecimals))) / Math.pow(10, nrDecimals);
		return number;
	}
	
	/**
	 * Calculates the Davies Bouldin Index for clusters generated by SimpleKMeans
	 * 
	 * @param clusterers the centroids of each cluster
	 * @param nrClust the number of clusters
	 * @param data the training data used
	 * @param assigments the assignments of each data within each cluster
	 * @return the corresponding index	  
	 */
	public double getDaviesBouldinIndex(Instances clusterers, int nrClust, Instances data, int[] assigments) {
		//double distance = 0.0;
		double daviesBouldin = 0.0;
		DistanceFunction m_DistanceFunction = new EuclideanDistance(data);
		

		for (int k = 0; k < nrClust; k++) {
			double max = Double.MIN_VALUE;
			double centroidDist = 0.0;
			double measureR = 0.0;
			
			double avgDist = 0.0;
			int nrDataInClust = 0;
			
			Instance centroid = clusterers.instance(k);
			
			for(int i = 0; i < data.numInstances(); i++) {
				if (assigments[i] == k) {
					avgDist += m_DistanceFunction.distance(centroid,data.instance(i));					
					nrDataInClust++;
				}
				
			}
			
			avgDist /= nrDataInClust;
			
			for (int j = 0; j < nrClust; j++) {
				if (k != j) {
					
					double avgDistDiffClust = 0.0;
					int nrDataInDiffClust = 0;
					
					Instance centroidDiffClust = clusterers.instance(j);
					
					for(int i = 0; i < data.numInstances(); i++) {
						if (assigments[i] == j) {
							avgDistDiffClust += m_DistanceFunction.distance(centroidDiffClust,data.instance(i));					
							nrDataInDiffClust++;
						}
						
					}
					
					avgDistDiffClust /= nrDataInDiffClust;
					
					centroidDist = m_DistanceFunction.distance(centroid,centroidDiffClust);
					
					measureR = (avgDist + avgDistDiffClust) / centroidDist;
					
					if (max < measureR) {
						max = measureR;
					}
				}
			}
			
			
			daviesBouldin += max;
		}
		
		daviesBouldin /= nrClust;
		
		return removeDecimals(daviesBouldin);
	}
	
	/**
	 * Calculates the Dunn Index for clusters generated by SimpleKMeans
	 * 
	 * @param clusterers the centroids of each cluster
	 * @param nrClust the number of clusters
	 * @param data the training data used
	 * @param assigments the assignments of each data within each cluster
	 * @return the corresponding index	  
	 */
	public double getDunnIndex(Instances clusterers, int nrClust, Instances data, int[] assigments) {
		
		double dunnIndex = 0.0;
		double minDistClust = Double.MAX_VALUE;
		double maxIntraClustDist = Double.MIN_VALUE;
		DistanceFunction m_DistanceFunction = new EuclideanDistance(data);
		
		for (int i = 0; i < nrClust - 1; i++) {
			for (int j = i + 1; j < nrClust; j++) {
				
				Instance centroidI = clusterers.instance(i);
				Instance centroidJ = clusterers.instance(j);
				
				double distClust = m_DistanceFunction.distance(centroidI, centroidJ);
				
				if (minDistClust > distClust) {
					minDistClust = distClust;
				}
			}
		}
		
		for (int i = 0; i < nrClust; i++) {
			
			double maxDist = Double.MIN_VALUE;
			
			Instances clusterData = new Instances(data);			
			
			for (int j = 0; j < clusterData.numInstances(); j++) {
				if (assigments[j] != i) {
					clusterData.remove(j);
				}
			}
			
			for (int j = 0; j < clusterData.size() - 1; j++) {
				for (int j2 = j + 1; j2 < clusterData.size(); j2++) {
					
					double dist = m_DistanceFunction.distance(clusterData.get(j), clusterData.get(j2));
					
					if (maxDist < dist) {
						maxDist = dist;
					}
				}
			}
			
			if (maxIntraClustDist < maxDist) {
				maxIntraClustDist = maxDist;
			}
		}
		
		dunnIndex = minDistClust / maxIntraClustDist;
		
		return removeDecimals(dunnIndex);
	}
	
	/**
	 * Calculates the Xi-Beni Index for clusters generated by SimpleKMeans
	 * 
	 * @param clusterers the centroids of each cluster
	 * @param nrClust the number of clusters
	 * @param data the training data used
	 * @param assigments the assignments of each data within each cluster
	 * @return the corresponding index	  
	 */
	public double getXiBeniIndex(Instances clusterers, int nrClust, Instances data, int[] assigments) {
		double xiBeniIndex = 0.0;
		double sum = 0.0;
		double min = Double.MAX_VALUE;
		DistanceFunction m_DistanceFunction = new EuclideanDistance(data);
		
		for (int i = 0; i < nrClust; i++) {
			
			Instance centroid = clusterers.instance(i);
			for (int j = 0; j < data.numInstances(); j++) {
				if (assigments[j] == i) {
					double dist = m_DistanceFunction.distance(centroid, data.get(j));
					
					sum += dist * dist;
				}
			}
		}
		
		for (int i = 0; i < nrClust - 1; i++) {
			for (int j = i + 1; j < nrClust; j++) {
				
				Instance centroidI = clusterers.instance(i);
				Instance centroidJ = clusterers.instance(j);
				
				double distClust = m_DistanceFunction.distance(centroidI, centroidJ);
				
				distClust *= distClust;
				
				if (min > distClust) {
					min = distClust;
				}
			}
		}
		
		xiBeniIndex = sum / (data.numInstances() * min);
		
		return removeDecimals(xiBeniIndex);
	}
	
	/**
	 * Calculates the Banfeld Raftery Index for clusters generated by SimpleKMeans
	 * 
	 * @param clusterers the centroids of each cluster
	 * @param nrClust the number of clusters
	 * @param data the training data used
	 * @param assigments the assignments of each data within each cluster
	 * @return the corresponding index	  
	 */
	public double getBanfeldRafteryIndex(Instances clusterers, int nrClust, Instances data, int[] assigments)
	{
		double bri = 0;
		double distance = 0;
		double clustCard = 0;
		double sum1 = 0;
		double sum2 = 0;
		
		DistanceFunction m_DistanceFunction = new EuclideanDistance(data);
		

		for(int k = 0; k < nrClust; k++)
		{
			Instance centroid = clusterers.instance(k);
			clustCard = 0;
			
			for(int i = 0; i < data.numInstances(); i++) 
			{
					if (assigments[i] == k)
					{
						clustCard++;
						distance = m_DistanceFunction.distance(data.instance(i),centroid);					
						sum1 += (distance * distance);
					}
					
			}
			
			sum2 += Math.log(sum1 / clustCard) * clustCard;
		}
		
		bri = sum2;
		
		if (bri < -999)
		{
			bri = -999;
		}
		
		
		return removeDecimals(bri);
	}
	
	/**
	 * Calculates the McClain Rao Index for clusters generated by SimpleKMeans
	 * 
	 * @param nrClust the number of clusters
	 * @param data the training data used
	 * @param assigments the assignments of each data within each cluster
	 * @return the corresponding index	  
	 */
	public double getMcClainRaoIndex(int nrClust, Instances data, int[] assigments)
	{
		double mri = 0;
		double nw = 0;
		double nb = 0;
		double sw = 0;
		double sb = 0;
		double sum1 = 0;
		double distance = 0;
		double clustCard = 0;
		
		double nrInst = data.numInstances();
		
		DistanceFunction m_DistanceFunction = new EuclideanDistance(data);
		
		for(int k = 0; k < nrClust; k++)
		{
			clustCard = 0;
			
			for(int i = 0; i < data.numInstances(); i++) 
			{
					if (assigments[i] == k)
					{
						clustCard++;
					}
					
			}
			
			sum1 += (clustCard * (clustCard - 1)) / 2;
		}
		
		nw = sum1;
		
		nb = ((nrInst * (nrInst - 1)) / 2) - nw;
		
		
		sum1 = 0;
		
		for(int k = 0; k < nrClust; k++)
		{
			
			for(int i = 0; i < data.numInstances(); i++)
			{
				if (assigments[i] == k)
				{
						
					for (int j = i + 1; j < data.numInstances(); j++) 
					{
						if (assigments[j] == k) 
						{
							distance = m_DistanceFunction.distance(data.instance(i),data.instance(j));
							sum1 += distance;
						}
					}
											
				}
					
			}
		}
		
		sw = sum1;
		
		sum1 = 0;
		
		for(int k = 0; k < nrClust; k++)
		{			
			for (int k1 = k + 1; k1 < nrClust; k1++)
			{
				for(int i = 0; i < data.numInstances(); i++)
				{
					if (assigments[i] == k)
					{							
						for (int j = i + 1; j < data.numInstances(); j++) 
						{
							if (assigments[j] == k1) 
							{
								distance = m_DistanceFunction.distance(data.instance(i),data.instance(j));
								sum1 += distance;
							}
						}												
					}						
				}
			}			
		}
		
		sb = sum1;
		
		mri = (nb / nw) * (sw / sb);
		
		
		return removeDecimals(mri);
	}
	
	/**
	 * Calculates the Ray Turi Index for clusters generated by SimpleKMeans
	 * 
	 * @param clusterers the centroids of each cluster
	 * @param nrClust the number of clusters
	 * @param data the training data used
	 * @param assigments the assignments of each data within each cluster
	 * @return the corresponding index	  
	 */
	public double getRayTuriIndex(Instances clusterers, int nrClust, Instances data, int[] assigments)
	{
		double rti = 0;
		double distance = 0;
		double wgss = 0;
		double minD = Double.MAX_VALUE;
		
		
		
		DistanceFunction m_DistanceFunction = new EuclideanDistance(data);		

		for(int k = 0; k < nrClust; k++)
		{
			Instance centroid = clusterers.instance(k);
			
			for(int i = 0; i < data.numInstances(); i++) 
			{
					if (assigments[i] == k)
					{
						distance = m_DistanceFunction.distance(data.instance(i),centroid);					
						wgss += (distance * distance);
					}
					
			}			
		}
		
		for(int k = 0; k < nrClust; k++)
		{
			Instance centroidk = clusterers.instance(k);
			
			for (int k1 = k + 1; k1 < nrClust; k1++) 
			{				
				Instance centroidk1 = clusterers.instance(k1);
				
				distance = m_DistanceFunction.distance(centroidk,centroidk1);	
				
				if (minD > distance) 
				{
					minD = distance;
				}
				
			}		
		}			
	
		rti = (1 / (double)data.numInstances()) * (wgss / minD);
		
		
		return removeDecimals(rti);
	}
	
	/**
	 * Calculates the Calinski Harabasz Index for clusters generated by SimpleKMeans
	 * 
	 * @param allDataCentroid the centroid from the cluster containing all the data
	 * @param clusterers the centroids of each cluster
	 * @param nrClust the number of clusters
	 * @param data the training data used
	 * @param assigments the assignments of each data within each cluster
	 * @return the corresponding index	  
	 */
	public double getCalinskiHarabaszIndex(Instance allDataCentroid, Instances clusterers, int nrClust, Instances data, int[] assigments)
	{
		double chi = 0;
		double distance = 0;
		double clustCard = 0;
		double bgss = 0;
		double wgss = 0;
		double nrData = data.numInstances();
		double nc = nrClust;
		
		DistanceFunction m_DistanceFunction = new EuclideanDistance(data);
		

		for(int k = 0; k < nrClust; k++)
		{
			Instance centroid = clusterers.instance(k);			
			
			for(int i = 0; i < data.numInstances(); i++) 
			{
					if (assigments[i] == k)
					{
						distance = m_DistanceFunction.distance(data.instance(i),centroid);					
						wgss += (distance * distance);
					}
					
			}
			
		}
		
		for(int k = 0; k < nrClust; k++)
		{
			Instance centroid = clusterers.instance(k);
			clustCard = 0;
			
			for(int i = 0; i < data.numInstances(); i++) 
			{
					if (assigments[i] == k)
					{
						clustCard++;
					}
					
			}
			
			distance = m_DistanceFunction.distance(centroid,allDataCentroid);
			bgss += clustCard * distance * distance;
			
		}
		
		
		chi = ((nrData - nc) / (nc - 1)) * (bgss / wgss);
		
		return removeDecimals(chi);
	}
	
	/**
	 * Calculates the Davies Bouldin Index for clusters generated by SimpleKMeans
	 * 
	 * @param allDataCentroid the centroid from the cluster containing all the data
	 * @param clusterers the centroids of each cluster
	 * @param nrClust the number of clusters
	 * @param data the training data used
	 * @param assigments the assignments of each data within each cluster
	 * @return the corresponding index	  
	 */
	public double getPBMindex(Instance allDataCentroid, Instances clusterers, int nrClust, Instances data, int[] assigments)
	{
		double pbm = 0;
		double distance = 0;
		double nc = nrClust;
		double db = Double.MIN_VALUE;
		double et = 0;
		double ew = 0;
		
		DistanceFunction m_DistanceFunction = new EuclideanDistance(data);
		

		for(int k = 0; k < nrClust; k++)
		{
			Instance centroid = clusterers.instance(k);			
			
			for(int i = 0; i < data.numInstances(); i++) 
			{
					if (assigments[i] == k)
					{
						distance = m_DistanceFunction.distance(data.instance(i),centroid);					
						ew += distance;
					}
					
			}
			
		}
		
		
			
		for(int i = 0; i < data.numInstances(); i++) 
		{				
			distance = m_DistanceFunction.distance(data.instance(i),allDataCentroid);					
			et += distance;	
		}
			
		
		for (int k = 0; k < nrClust; k++)
		{
			Instance centroidk = clusterers.instance(k);	
			
			for (int k1 = k + 1; k1 < nrClust; k1++) 
			{
				Instance centroidk1 = clusterers.instance(k1);	
				distance = m_DistanceFunction.distance(centroidk,centroidk1);
				
				if (db < distance)
				{
					db = distance;
				}
			}
		}
		
		pbm = (1/nc) * (et/ew) * db;
		
		pbm *= pbm;
		
		return removeDecimals(pbm);
	}
}