#pragma once

class MUtils
{
public:
	template<typename T>
	static T* GetMPlayerComponent(AActor* PlayerPawn)
	{
		if (!PlayerPawn) return nullptr;

		const auto Component = PlayerPawn->GetComponentByClass(T::StaticClass());
		return Cast<T>(Component);
	}
};
