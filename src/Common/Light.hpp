/*
 * Light.hpp
 *
 *  Created on: 7 Aug 2009
 *      Author: stefan
 */

#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <Maoni/Color.hpp>
#include <Maoni/Vector.hpp>

class Light
{
public:
	Light() :
		name("Light"), position(0.f, 0.f, 1.f, 0.f), ambient(0.f, 0.f, 0.f, 1.f), //
				diffuse(0.f, 0.f, 0.f, 1.f), specular(0.f, 0.f, 0.f, 1.f), //
				const_att(1.f), lin_att(0.f), quad_att(0.f), //
				is_spot(false), spot_direction(0.f, 0.f, -1.f), cut_off(180.f), //
				exponent(0.f), is_on(true), show_bulp(false), is_light0(false)
	{
		calcLightBox(0.3);
	}



private:
	std::string name;
	Vector4 position;
	Color ambient;
	Color diffuse;
	Color specular;
	float const_att;
	float lin_att;
	float quad_att;
	bool is_spot;
	Vector3 spot_direction;
	float cut_off;
	float exponent;
	bool is_on;
	bool show_bulp;
	Vector3 light_box[8];
	bool is_light0;

    void calcLightBox(float scaler){
		//std::cout << position[0] << " " << position[1] << " " << position[2] << std::endl;


    	light_box[0] = Vector3(position[0]-scaler,position[1]-scaler,position[2]-scaler);
    	light_box[1] = Vector3(position[0]-scaler,position[1]-scaler,position[2]+scaler);
    	light_box[2] = Vector3(position[0]-scaler,position[1]+scaler,position[2]-scaler);
    	light_box[3] = Vector3(position[0]-scaler,position[1]+scaler,position[2]+scaler);
    	light_box[4] = Vector3(position[0]+scaler,position[1]-scaler,position[2]-scaler);
    	light_box[5] = Vector3(position[0]+scaler,position[1]-scaler,position[2]+scaler);
    	light_box[6] = Vector3(position[0]+scaler,position[1]+scaler,position[2]-scaler);
    	light_box[7] = Vector3(position[0]+scaler,position[1]+scaler,position[2]+scaler);
    }

public:
    Color const& getAmbient() const
    {
        return ambient;
    }

    float getConst_att() const
    {
        return const_att;
    }

    float getCut_off() const
    {
        return cut_off;
    }

    Color const& getDiffuse() const
    {
        return diffuse;
    }

    float getExponent() const
    {
        return exponent;
    }

    bool getIs_light0() const
    {
        return is_light0;
    }

    bool getIs_on() const
    {
        return is_on;
    }

    bool getIs_spot() const
    {
        return is_spot;
    }

    float getLin_att() const
    {
        return lin_att;
    }

    std::string getName() const
    {
        return name;
    }

    Vector4 getPosition() const
    {
        return position;
    }

    float getQuad_att() const
    {
        return quad_att;
    }

    bool getShow_bulp() const
    {
        return show_bulp;
    }

    Color const& getSpecular() const
    {
        return specular;
    }

    Vector3 getSpot_direction() const
    {
        return spot_direction;
    }

    Vector3 getLight_box(int corner) const
    {
    	return light_box[corner];
    }

    void setAmbient(Color const& ambient)
    {
        this->ambient = ambient;
    }

    void setConst_att(float const_att)
    {
        this->const_att = const_att;
    }

    void setCut_off(float cut_off)
    {
        this->cut_off = cut_off;
    }

    void setDiffuse(Color const& diffuse)
    {
        this->diffuse = diffuse;
    }

    void setExponent(float exponent)
    {
        this->exponent = exponent;
    }

    void setIs_light0(bool is_light0)
    {
        this->is_light0 = is_light0;
    }

    void setIs_on(bool is_on)
    {
        this->is_on = is_on;
    }

    void setIs_spot(bool is_spot)
    {
        this->is_spot = is_spot;
    }

    void setLin_att(float lin_att)
    {
        this->lin_att = lin_att;
    }

    void setName(std::string name)
    {
        this->name = name;
    }

    void setPosition(Vector4 position)
    {
        this->position = position;
    }

    void setQuad_att(float quad_att)
    {
        this->quad_att = quad_att;
    }

    void setShow_bulp(bool show_bulp)
    {
        this->show_bulp = show_bulp;
    }

    void setSpecular(Color const& specular)
    {
        this->specular = specular;
    }

    void setSpot_direction(Vector3 spot_direction)
    {
        this->spot_direction = spot_direction;
    }

    void recalcLightBox(float scaler){
    	calcLightBox(scaler);
    }

    void apply(int id) const;
};

#endif /* LIGHT_HPP */
