#include "StudentFeatureAdapterToLibrary.h"

namespace solid_edu
{
	StudentFeatureAdapterToLibrary::StudentFeatureAdapterToLibrary(std::unique_ptr<solid_edu::IStudentFeature> feature)
		: studentFeatureAdaptee{ std::move(feature) } {}

	bool StudentFeatureAdapterToLibrary::hasFeature(const std::string& username) const
	{
		return studentFeatureAdaptee->hasFeature(username);
	}
}
