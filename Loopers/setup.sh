
echo "Remember to run setup.sh at the VVVBabyMaker level."
echo "This is not strictly needed, but some CORE files are linked in the macros."
echo " "
echo "Creating directories"
echo "mkdir data"
mkdir data
echo "mkdir plots"
mkdir plots
echo "mkdir rootfiles"
mkdir rootfiles

echo "Copy rootfiles for scale factors and fake rates (partially still to be updated)"
echo "cp /nfs-7/userdata/haweber/VVVhelperfiles/*.root rootfiles/."
cp /nfs-7/userdata/haweber/VVVhelperfiles/*.root rootfiles/.
echo "/nfs-7/userdata/haweber/VVVhelperfiles/*JSON.txt data/."
cp /nfs-7/userdata/haweber/VVVhelperfiles/*JSON.txt data/.

echo " "
echo "Done setup."
